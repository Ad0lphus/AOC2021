import java.io.*
fun print_day_14() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 14" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Extended Polymerization -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_14()
    Day14().part_1()
    Day14().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day14 {
    val lines = File("../Input/day14.txt").readLines()
    val polyTemplate = lines.first()

    fun part_1() {
        val pairInsertions = lines.drop(2).map {
            val (pair, insertion) = it.split(" -> ")
            pair to insertion
        }

        var polyIteration = polyTemplate
        for (step in 1..10) {
            polyIteration = polyIteration.fold("") { str, curr ->
                val pairCheck = "" + (str.lastOrNull() ?: "") + curr
                val insert = pairInsertions.find { it.first == pairCheck } ?.second ?: ""

                str + insert + curr
            }
        }

        val elementCounts = polyIteration.groupBy { it }.map { it.key to it.value.size }.sortedBy { it.second }
        val ans = elementCounts.last().second - elementCounts.first().second
        println("Puzzle 1: $ans")
    }

    fun part_2() {
        val insertPattern = lines.drop(2).map { it.split(" -> ") }.associate { it[0] to it[1] }
        var pairFrequency = mutableMapOf<String, Long>()
        polyTemplate.windowed(2).forEach{ pairFrequency.put(it, pairFrequency.getOrDefault(it, 0) + 1) }
        for (step in 1..40) {
            val updatedFrequencies = mutableMapOf<String, Long>()
            pairFrequency.forEach {
                val key1 = it.key[0] + insertPattern[it.key]!!
                val key2 = insertPattern[it.key]!! + it.key[1]
                updatedFrequencies.put(key1, updatedFrequencies.getOrDefault(key1, 0) + it.value)
                updatedFrequencies.put(key2, updatedFrequencies.getOrDefault(key2, 0) + it.value)
            }
            pairFrequency = updatedFrequencies
        }
        val charFrequency = pairFrequency.toList().fold(mutableMapOf<Char, Long>()) { acc, pair ->
            acc.put(pair.first[0], acc.getOrDefault(pair.first[0], 0) + pair.second)
            acc
        }
        charFrequency.put(polyTemplate.last(), charFrequency.getOrDefault(polyTemplate.last(), 0) + 1)
        val sorted = charFrequency.values.sorted()
        val ans = sorted.last() - sorted.first()
        println("Puzzle 2: $ans")
    }
}