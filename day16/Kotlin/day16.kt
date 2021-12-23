import java.io.*
fun print_day_16() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 16" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Packet Decoder -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_16() 
    Day16().part_1()
    Day16().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day16 {
    private val filedata = File("../Input/day16.txt").readLines().first()
    private val binary = filedata.fold("") { acc, c -> acc + c.toHexVal() }
    private val bits = BitsReader(binary)

    class BitsReader(val bits: String) {
        private var cursor: Int = 0
        fun takeNext(num: Int): String {
            val res = bits.substring(cursor, cursor + num)
            cursor += num
            return res
        }

        fun calcTarget(len: Int): Int = cursor + len
        fun hasReachedCursor(cursorTarget: Int): Boolean = cursor >= cursorTarget
    }

    sealed class Packet(val version: Int) {
        abstract fun calcVal(): Long

        class Literal(version: Int, val value: Long) : Packet(version) {
            override fun calcVal() = value
        }

        class Operator(version: Int, val opType: Int, val subpackets: List<Packet>) :
                Packet(version) {
            override fun calcVal(): Long {
                return when (opType) {
                    0 -> subpackets.sumOf { it.calcVal() } 
                    1 ->
                            subpackets.fold(1L) { sum, p ->
                                sum * p.calcVal()
                            } 
                    2 -> subpackets.minOf { it.calcVal() } 
                    3 -> subpackets.maxOf { it.calcVal() } 
                    5 ->
                            if (subpackets[0].calcVal() > subpackets[1].calcVal()) 1
                            else 0 
                    6 ->
                            if (subpackets[0].calcVal() < subpackets[1].calcVal()) 1
                            else 0 
                    7 ->
                            if (subpackets[0].calcVal() == subpackets[1].calcVal()) 1
                            else 0 
                    else -> 0
                }
            }
        }
    }

    fun readPacket(): Packet {

        val v = bits.takeNext(3).toInt(2)
        val t = bits.takeNext(3).toInt(2)

        if (t == 4) {
            var continueBit: Boolean = true
            var res = ""
            while (continueBit) {
                continueBit = bits.takeNext(1) == "1"
                res += bits.takeNext(4)
            }

            return Packet.Literal(v, res.toLong(2))
        } else {
            val lType = bits.takeNext(1).toInt(2)
            val subpackets =
                    if (lType == 1) {
                        val numSubPackets = bits.takeNext(11).toInt(2)
                        (1..numSubPackets).map { readPacket() }
                    } else {
                        val len = bits.takeNext(15).toInt(2)
                        val cursorTarget = bits.calcTarget(len)
                        val subpackets = mutableListOf<Packet>()
                        while (!bits.hasReachedCursor(cursorTarget)) {
                            subpackets.add(readPacket())
                        }
                        subpackets
                    }
            return Packet.Operator(v, t, subpackets)
        }
    }

    private fun sumAllPackets(packet: Packet): Long {
        return when (packet) {
            is Packet.Literal -> packet.version.toLong()
            is Packet.Operator -> packet.version + packet.subpackets.sumOf { sumAllPackets(it) }
        }
    }

    fun part_1() = println("Puzzle 1: " + sumAllPackets(readPacket()))
    fun part_2() = println("Puzzle 2: " + readPacket().calcVal())

    fun Char.toHexVal() = this.digitToInt(16).toString(2).padStart(4, '0')
}
