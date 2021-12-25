import java.io.*
import java.math.BigInteger
import java.security.MessageDigest

fun print_day_25() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 25" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Sea Cucumber -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun readInput25(name: String) = File("../Input", "$name.txt").readLines()
fun main() {
    print_day_25() 
    fun List<String>.parse() = Array(size) { rowIndex -> this[rowIndex].toCharArray() }

    fun Array<CharArray>.move(): Array<CharArray> {
        val height = size
        val width = first().size

        val result = Array(height) { CharArray(width) { '.' } }

        for (i in 0 until height) {
            for (j in 0 until width) {
                if (this[i][j] == '>') {
                    if (this[i][(j + 1) % width] == '.') {
                        result[i][(j + 1) % width] = '>'
                    } else {
                        result[i][j] = '>'
                    }
                }
            }
        }

        for (i in 0 until height) {
            for (j in 0 until width) {
                if (this[i][j] == 'v') {
                    if (
                        (this[(i + 1) % height][j] == '.' && result[(i + 1) % height][j] == '.' ) ||
                        (this[(i + 1) % height][j] == '>' && result[(i + 1) % height][j] == '.')
                    ) {
                        result[(i + 1) % height][j] = 'v'
                    } else {
                        result[i][j] = 'v'
                    }
                }
            }
        }
        return result
    }

    fun part1(
        input: List<String>
    ) = input.parse().let { array ->
        var steps = 0
        var result = array

        while (true) {
            steps++
            val movedArray = result.move()
            if (movedArray.contentDeepEquals(result)) break
            result = movedArray
        }

        return@let steps
    }

    

    val input = readInput25("day25")
    println("Puzzle 1: " + part1(input))
    println("Puzzle 2: Completed :))")
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}