import java.io.*

fun print_day_4() {
    
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 4" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Giant Squid -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)

    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_4()
    print("Puzzle 1: ")
    Day4().part_1()
    print("Puzzle 2: ")
    Day4().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day4 {

    private val lines = File("../Input/day4.txt").readLines()

    private val drawOrder = lines[0].split(",").map { it.toInt() }
    private val boards =
            lines.drop(1).windowed(6, 6) {
                it.drop(1).map { line ->
                    line.trim().split("  ", " ").map { numStr -> numStr.toInt() }
                }
            }

    fun checkLine(line: List<Int>, drawn: List<Int>) = drawn.containsAll(line)
    fun checkBoard(board: List<List<Int>>, drawn: List<Int>): Boolean {

        val hasHorizontalLine = board.any { checkLine(it, drawn) }
        val flippedBoard =
                (board[0].indices).map { outer ->
                    (board.indices).map { inner -> board[inner][outer] }
                }
        val hasVerticalLine = flippedBoard.any { checkLine(it, drawn) }

        return hasHorizontalLine || hasVerticalLine
    }

    fun part_1() {

        for (i in 5..drawOrder.size) {
            val currentDraw = drawOrder.take(i)
            boards.forEach() {
                if (checkBoard(it, currentDraw)) {
                    return calculateWinner(it, currentDraw)
                }
            }
        }
    }

    private fun calculateWinner(board: List<List<Int>>, currentDraw: List<Int>) {
        println(board.flatten().filter { !currentDraw.contains(it) }.sum() * currentDraw.last())
    }

    fun part_2() {
        val winners = mutableListOf<Int>()

        for (i in 5..drawOrder.size) {
            val currentDraw = drawOrder.take(i)
            boards.forEachIndexed() { index, board ->
                if (!winners.contains(index) && checkBoard(board, currentDraw)) {
                    winners.add(index)
                    if (winners.size == boards.size) {
                        return calculateWinner(board, currentDraw)
                    }
                }
            }
        }
    }
}
