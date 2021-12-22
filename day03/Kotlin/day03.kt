import java.io.*
fun print_day_3() {
    
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 3" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Binary Diagnostic -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)

    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_3()
    Day3().part_1()
    Day3().part_2()
    println("\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day3 {

    val lines = File("../Input/day3.txt").readLines()

    fun part_1() {
        val matrix = lines.map { s -> s.toCharArray().map { c -> c.digitToInt() } }
        var gamma = ""
        var epsilon = ""

        for(idx in matrix[0].indices) {
            val res = matrix.partition { it[idx] == 1 }
            gamma += if (res.first.count() > res.second.count())  "1" else "0"
            epsilon +=  if (res.first.count() > res.second.count())  "0" else "1"
        }

        val answer = gamma.toInt(2) * epsilon.toInt(2)
        println("Puzzle 1: " + answer)
    }

    fun part_2() {
        fun splitAndRecurse(list: List<List<Int>>, index: Int, max: Boolean) : List<Int> {
            if (list.size == 1) return list[0]

            val res = list.partition { it[index] == 1 }
            val keep =
                if (res.first.count() >= res.second.count())
                    if (max) res.first else res.second
                else
                    if (max) res.second else res.first
            return splitAndRecurse(keep, index+1,  max)
        }

        val matrix = lines.map { s -> s.toCharArray().map { c -> c.digitToInt() } }
        val oxygen = splitAndRecurse(matrix, 0, true)
        val co2 = splitAndRecurse(matrix, 0, false)

        val oxygenDecimal = oxygen.joinToString("").toInt(2)
        val co2Decimal = co2.joinToString("").toInt(2)

        println("Puzzle 2: " + oxygenDecimal * co2Decimal +"\n")
    }
}