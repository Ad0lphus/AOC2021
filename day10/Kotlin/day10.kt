import java.io.*
import java.util.*
fun print_day_10() {
    
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 10" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Syntax Scoring -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_10()
    Day10().part_1()
    Day10().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day10 {
    private val lines = File("../Input/day10.txt").readLines()
    private val opening = arrayOf('{', '[', '(', '<')
    private val bracketPairs = mapOf('{' to '}', '[' to ']', '(' to ')', '<' to '>')

    private fun checkMatchingBrackets(stack: Stack<Char>, remainingChars: String): Int {
        if (remainingChars.isEmpty()) return 0

        val c = remainingChars.first()
        if (c in opening) {
            stack.push(c)
        }
        else {
            val matchTo = stack.pop()
            if (bracketPairs[matchTo] != c) {
                return when(c) {
                    ')' -> 3
                    ']' -> 57
                    '}' -> 1197
                    '>' -> 25137
                    else -> 0
                }
            }
        }
        return checkMatchingBrackets(stack, remainingChars.substring(1))
    }

    fun part_1() {
        val total = lines.sumOf {
            checkMatchingBrackets(Stack<Char>(), it)
        }
        println("Puzzle 1: " + total)
    }

    fun part_2() {
        val total = lines.map {
            val stack = Stack<Char>()
            if (checkMatchingBrackets(stack, it) == 0) {
                stack.foldRight(0L) { c, acc ->
                    acc * 5 + when(bracketPairs[c]) {
                        ')' -> 1
                        ']' -> 2
                        '}' -> 3
                        '>' -> 4
                        else -> 0
                    }
                }
            }
            else 0
        }
        .filterNot { it == 0L }
        .sorted()

        println("Puzzle 2: " + total[(total.size / 2)])
    }
}