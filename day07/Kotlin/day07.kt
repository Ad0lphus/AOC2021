import java.io.*
import kotlin.math.abs
fun print_day_7() {
    
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 7" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet The Treachery of Whales -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)

    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_7()
    Day7().part_1()
    Day7().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day7 {
    val crabs = File("../Input/day7.txt").readLines().first().split(",").map{it.toInt()}

    fun part_1() {
        val min = crabs.minOrNull()!!
        val max = crabs.maxOrNull()!!

        var lowest = Int.MAX_VALUE

        for(i in min .. max) {
            var fuelUsed = 0
            for(crab in crabs) { fuelUsed += abs(crab - i) }

            if (fuelUsed < lowest) {
                lowest = fuelUsed
            }
        }
        println("Puzzle 1: $lowest")
    }

    fun part_2() {

        val min = crabs.minOrNull()!!
        val max = crabs.maxOrNull()!!

        var lowest = Int.MAX_VALUE

        for(i in min .. max) {
            var fuelUsed = 0
            for(crab in crabs) { fuelUsed += calcFibIncrement(abs(crab - i)) }

            if (fuelUsed < lowest) {
                lowest = fuelUsed
            }
        }
        println("Puzzle 2: $lowest")
    }
    fun calcFibIncrement(increment: Int, incrementBy: Int = 0): Int {
        return if (increment == 0)
            incrementBy
        else
            calcFibIncrement(increment - 1, incrementBy + 1) + incrementBy
    }

}