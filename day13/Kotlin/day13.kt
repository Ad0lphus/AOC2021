import java.io.*
fun print_day_13() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 13" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Transparent Origami -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_13()
    Day13().part_1()
    Day13().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day13 {
    private val lines = File("../Input/day13.txt").readLines()
    private val coords = lines.takeWhile { it.trim() != "" }.map {
        val (x, y) = it.split(",")
        x.toInt() to y.toInt()
    }
    private val folds = lines.drop(coords.size + 1)

    fun part_1() {

        val maxX = coords.maxOf { it.first }
        val maxY = coords.maxOf { it.second }

        val yFold = folds.first().startsWith("fold along y")
        val foldAmount = folds.first().split("=")[1].toInt()

        val afterFold = if (yFold) {
                val newCoords = coords.filter { it.second < foldAmount }.toMutableList()
                for (pair in coords.filter {it.second > foldAmount} ) {
                    newCoords.add(pair.first to maxY - pair.second)
                }
                newCoords
            }
            else  {
                val newCoords = coords.filter { it.first < foldAmount }.toMutableList()
                for (pair in coords.filter {it.first > foldAmount} ) {
                    newCoords.add(maxX - pair.first to pair.second)
                }
                newCoords
            }

        println("Puzzle 1: " + afterFold.distinct().size)
    }

    fun part_2() {

        var foldedCoords = coords
        folds.forEach { fold ->
            val maxX = foldedCoords.maxOf { it.first }
            val maxY = foldedCoords.maxOf { it.second }

            val yFold = fold.startsWith("fold along y")
            val foldAmount = fold.split("=")[1].toInt()

            val afterFold = if (yFold) {
                val newCoords = foldedCoords.filter { it.second < foldAmount }.toMutableList()
                for (pair in foldedCoords.filter {it.second > foldAmount} ) {
                    newCoords.add(pair.first to maxY - pair.second)
                }
                newCoords
            }
            else  {
                val newCoords = foldedCoords.filter { it.first < foldAmount }.toMutableList()
                for (pair in foldedCoords.filter {it.first > foldAmount} ) {
                    newCoords.add(maxX - pair.first to pair.second)
                }
                newCoords
            }

            foldedCoords = afterFold
        }

        val maxX = foldedCoords.maxOf { it.first }
        val maxY = foldedCoords.maxOf { it.second }
        println("Puzzle 2: ")
        for (y in 0..maxY) {
            for (x in 0..maxX) {
                print( if ((x to y) in foldedCoords) "#" else " ")
            }
            println()
        }
    }
}