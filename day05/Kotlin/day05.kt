import java.io.*
import kotlin.math.abs

fun print_day_5() {
    
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 5" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Hydrothermal Venture -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)

    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}

fun main() {
    print_day_5() 
    Day5().puzzle1()
    Day5().puzzle2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day5 {
    data class Point(val x:Int, val y: Int)

    private val lines = File("../Input/day5.txt").readLines()
    private val points = lines.map { line ->
        line.split(" -> ").map { point ->
            val pairs = point.split(",")
            Point(pairs[0].toInt(), pairs[1].toInt())
        }
    }

    fun puzzle1() {

        val map2d = Array(1000) { Array(1000) { 0 } }

        points.forEach() {
            if (it[0].x == it[1].x) {
                val min = Math.min(it[0].y, it[1].y)
                val max = Math.max(it[0].y, it[1].y)

                for(i in min..max) {
                    map2d[i][it[0].x]++
                }
            }
            else if (it[0].y == it[1].y) {
                val min = Math.min(it[0].x, it[1].x)
                val max = Math.max(it[0].x, it[1].x)

                for(i in min..max) {
                    map2d[it[0].y][i]++
                }
            }
        }

        val overlaps = map2d.sumOf { it.count { point -> point >= 2 } }

        println("Puzzle 1: " + overlaps)

    }

    fun puzzle2() {

        val map2d = Array(1000) { Array(1000) { 0 } }
        points.forEach() {
            if (it[0].x == it[1].x) {
                val min = Math.min(it[0].y, it[1].y)
                val max = Math.max(it[0].y, it[1].y)

                for(i in min..max) {
                    map2d[i][it[0].x]++
                }
            }
            else if (it[0].y == it[1].y) {
                val min = Math.min(it[0].x, it[1].x)
                val max = Math.max(it[0].x, it[1].x)

                for(i in min..max) {
                    map2d[it[0].y][i]++
                }
            }
            else if ( isDiagonal(it[0], it[1]) ) {
                val len = abs(it[0].x - it[1].x)
                val xStep = if (it[1].x - it[0].x > 0) 1 else -1
                val yStep = if (it[1].y - it[0].y > 0) 1 else -1

                for(i in 0..len) {
                    val y = it[0].y + (i*yStep)
                    val x = it[0].x + (i*xStep)
                    map2d[y][x]++
                }
            }
        }

        val overlaps = map2d.sumOf { it.count { point -> point >= 2 } }
        println("Puzzle 2: " + overlaps)
    }
    private fun isDiagonal(p1: Point, p2: Point): Boolean = abs(p1.x - p2.x) == abs(p1.y - p2.y)
}