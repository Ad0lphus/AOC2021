import java.io.*
import java.io.File

fun print_day_1() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 1" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Sonar Sweep -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)

    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}

fun main() {
    print_day_1()
    Day1().puzzle1()
    Day1().puzzle2()
    println("\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day1 {
    private val file = File("../Input/day1.txt")

    fun puzzle1() {

        val lines = file.readLines().map { it.toInt() }

        val increases = lines.windowed(2, 1) { if (it[1] > it[0]) 1 else 0 }.sum()

        println("Puzzle 1: " + increases)
    }

    fun puzzle2() {
        val lines = file.readLines().map { it.toInt() }

        val increases =
                lines
                        .windowed(4, 1) {
                            val w1 = it[0] + it[1] + it[2]
                            val w2 = it[1] + it[2] + it[3]

                            if (w2 > w1) 1 else 0
                        }
                        .sum()

        println("Puzzle 2: " + increases + "\n")
    }
}
