import java.io.*

fun print_day_2() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 2" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Dive ! -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)

    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}

fun main() {
    print_day_2()
    Day2().puzzle1()
    Day2().puzzle2()
    println("\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day2 {
    val lines = File("../Input/day2.txt").readLines()

    fun puzzle1() {
        var horizontal = 0
        var depth = 0

        lines.forEach() {
            val instructions = it.split(" ")
            val direction = instructions[0]
            val amount = instructions[1].toInt()

            when (direction) {
                "forward" -> horizontal += amount
                "down" -> depth += amount
                "up" -> depth -= amount
            }
        }
        println("Puzzle 2: " + horizontal * depth)
    }

    fun puzzle2() {
        var horizontal = 0
        var depth = 0
        var aim = 0

        lines.forEach() {
            val instructions = it.split(" ")
            val direction = instructions[0]
            val amount = instructions[1].toInt()

            when (direction) {
                "forward" -> {
                    horizontal += amount
                    depth += aim * amount
                }
                "down" -> aim += amount
                "up" -> aim -= amount
            }
        }
        println("Puzzle 2: " + horizontal * depth + "\n")
    }
}
