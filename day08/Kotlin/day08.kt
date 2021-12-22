import java.io.*

fun print_day_8() {
    
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 8" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Seven Segment Search -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)

    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_8()
    Day8().part_1()
    Day8().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day8 {
    private val lines = File("../Input/day8.txt").readLines().map { it.split("|")[0].trim() to it.split("|")[1].trim() }

    fun part_1() {
        val uniqueLengths = listOf(2, 3, 4, 7)

        var totalUnique = 0
        for((_, output) in lines) {
            output.split(" ").forEach {
                if(it.length in uniqueLengths) totalUnique++
            }
        }
        println("Puzzle 1: " + totalUnique)
    }

    fun part_2() {
        var total = 0
        for((input, output) in lines) {
            val displays = mutableMapOf<String, Int>()
            val inputs = input.split(" ").map{ it.sortChars() }

            val one = inputs.first { it.length == 2 }
            val four = inputs.first { it.length == 4 }
            val seven = inputs.first { it.length == 3 }
            val eight = inputs.first { it.length == 7 }
            val nine = inputs.first { it.length == 6 && it.containsAll(four) }

            displays[one] = 1
            displays[four] = 4
            displays[seven] = 7
            displays[eight] = 8
            displays[nine] = 9
            displays[inputs.first { it.length == 6 && it.containsAll(seven) && !it.containsAll(four) }] = 0
            displays[inputs.first { it.length == 6 && !it.containsAll(one) }] = 6
            displays[inputs.first { it.length == 5 && it.containsAll(one) }] = 3
            displays[inputs.first { it.length == 5 && !it.containsAll(one) && nine.containsAll(it) }] = 5
            displays[inputs.first { it.length == 5 && !it.containsAll(one) && !nine.containsAll(it) }] = 2

            total += output.split(" ").fold("") { number, outputVal ->
                number + displays[outputVal.sortChars()].toString()
            }.toInt()
        }

        println("Puzzle 2: " + total)
    }

    private fun String.sortChars() = this.toCharArray().sorted().joinToString("")
    private fun String.containsAll(chars: String) = this.toList().containsAll(chars.toList())
}