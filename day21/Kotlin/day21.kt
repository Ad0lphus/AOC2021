import java.io.*
import java.util.concurrent.atomic.AtomicInteger

fun print_day_21() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 21" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Dirac Dice -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}

fun main() {
    print_day_21()
    Day21().part1()
    Day21().part2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day21 {
    fun part1() {
        val startPos = File("../Input/day21.txt").readLines().map { it.last().digitToInt() }
        val scores = intArrayOf(0, 0)
        val space = startPos.toIntArray()
        val dice = AtomicInteger()
        var diceRolls = 0

        fun nextRoll(): Int {
            if (dice.get() >= 100) dice.set(0)
            diceRolls++
            return dice.incrementAndGet()
        }

        while (true) {
            repeat(2) {
                val roll = nextRoll() + nextRoll() + nextRoll()
                space[it] = (space[it] + roll) % 10
                scores[it] += if (space[it] != 0) space[it] else 10

                if (scores[it] >= 1000) {
                    println("Puzzle 1: " + scores[(it + 1) % 2] * diceRolls)
                    return
                }
            }
        }
    }

    fun part2() {
        data class Universe(val p1: Int, val p2: Int, val s1: Int, val s2: Int)

        val startPos = File("../Input/day21.txt").readLines().map { it.last().digitToInt() }

        val dp = mutableMapOf<Universe, Pair<Long, Long>>()
        fun solve(u: Universe): Pair<Long, Long> {
            dp[u]?.let {
                return it
            }
            if (u.s1 >= 21) return 1L to 0L
            if (u.s2 >= 21) return 0L to 1L
            var ans = 0L to 0L
            for (d1 in 1..3) for (d2 in 1..3) for (d3 in 1..3) {
                val newP1 = (u.p1 + d1 + d2 + d3 - 1) % 10 + 1
                val newS1 = u.s1 + newP1
                val (x, y) = solve(Universe(u.p2, newP1, u.s2, newS1))
                ans = ans.first + y to ans.second + x
            }
            return ans.also { dp[u] = it }
        }
        println(
                "Puzzle 2: " +
                        solve(Universe(startPos[0], startPos[1], 0, 0)).let {
                            maxOf(it.first, it.second)
                        }
        )
    }
}
