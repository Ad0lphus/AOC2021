import java.io.*
import java.math.BigInteger
import java.security.MessageDigest

fun print_day_24() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 24" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Arithmetic Logic Unit -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun readInput(name: String) = File("../Input", "$name.txt").readLines()

fun readText(name: String) = File("Input", "$name.txt").readText()

fun String.md5(): String = BigInteger(1, MessageDigest.getInstance("MD5").digest(toByteArray())).toString(16)

fun main() {
    print_day_24() 
    fun part1(blocks: List<List<String>>): Long {
        val result = MutableList(14) { -1 }
        val buffer = ArrayDeque<Pair<Int, Int>>()
        blocks.forEachIndexed { index, instructions ->
            if ("div z 26" in instructions) {
                val offset = instructions.last { it.startsWith("add x") }.split(" ").last().toInt()
                val (lastIndex, lastOffset) = buffer.removeFirst()
                val difference = offset + lastOffset
                if (difference >= 0) {
                    result[lastIndex] = 9 - difference
                    result[index] = 9
                } else {
                    result[lastIndex] = 9
                    result[index] = 9 + difference
                }
            } else buffer.addFirst(index to instructions.last { it.startsWith("add y") }.split(" ").last().toInt())
        }

        return result.joinToString("").toLong()
    }

    fun part2(blocks: List<List<String>>): Long {
        val result = MutableList(14) { -1 }
        val buffer = ArrayDeque<Pair<Int, Int>>()
        blocks.forEachIndexed { index, instructions ->
            if ("div z 26" in instructions) {
                val offset = instructions.last { it.startsWith("add x") }.split(" ").last().toInt()
                val (lastIndex, lastOffset) = buffer.removeFirst()
                val difference = offset + lastOffset
                if (difference >= 0) {
                    result[lastIndex] = 1
                    result[index] = 1 + difference
                } else {
                    result[lastIndex] = 1 - difference
                    result[index] = 1
                }
            } else buffer.addFirst(index to instructions.last { it.startsWith("add y") }.split(" ").last().toInt())
        }

        return result.joinToString("").toLong()
    }

    val input = readInput("day24")

    fun String.toVariable(): Variable = Variable(this.let { it[0] })

    fun String.toToken(): Token = try {
        Literal1(this.toLong())
    } catch (ex: Exception) {
        Variable(this[0])
    }

    val commands = input.map { line ->
        val parts = line.split(" ")

        when (parts.first()) {
            "inp" -> Inp(parts[1].toVariable())
            "mul" -> Mul(parts[1].toVariable(), parts[2].toToken())
            "add" -> Add(parts[1].toVariable(), parts[2].toToken())
            "mod" -> Mod(parts[1].toVariable(), parts[2].toToken())
            "div" -> Div(parts[1].toVariable(), parts[2].toToken())
            "eql" -> Eql(parts[1].toVariable(), parts[2].toToken())
            else -> error("Cannot parse $parts")
        }
    }

    println("Puzzle 1: " + part1(input.chunked(18)))
    println("Puzzle 2: " + part2(input.chunked(18)))
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

sealed class Token
data class Literal1(val v: Long) : Token()
data class Variable(val v: Char) : Token()

sealed class Command
data class Inp(val a: Variable) : Command()
data class Add(val a: Variable, val b: Token) : Command()
data class Mul(val a: Variable, val b: Token) : Command()
data class Mod(val a: Variable, val b: Token) : Command()
data class Div(val a: Variable, val b: Token) : Command()
data class Eql(val a: Variable, val b: Token) : Command()

