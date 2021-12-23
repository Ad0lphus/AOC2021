import java.io.*
fun print_day_11() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 11" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Dumbo Octopus -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_11()
    Day11().part_1()
    Day11().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day11 {
    private val octogrid = File("../Input/day11.txt").readLines().map { it.toCharArray().map { c -> c.digitToInt() }.toMutableList() }.toMutableList()
    data class GridPoint(val x:Int, val y:Int) {
        fun neighbours(xBoundary: Int, yBoundary: Int): List<GridPoint> =
            (-1 .. 1).map { yOffset ->  (-1 .. 1).map { xOffset -> GridPoint(x+xOffset, y+yOffset)  } }.flatten()
                .filter {
                    it.x in 0 until xBoundary && it.y  in 0 until yBoundary && !(it.x == x && it.y == y)
                }
    }
    fun part_1() {
        var totalFlashes = 0
        for(step in 1..100) {
            val flashed = mutableListOf<GridPoint>()
            for (y in octogrid.indices) {
                for (x in octogrid[y].indices) {
                    octogrid[y][x]++
                }
            }
            do {
                val newFlashes = mutableListOf<GridPoint>()
                for (y in octogrid.indices) {
                    for (x in octogrid[y].indices) {
                        val gp = GridPoint(x, y)
                        if (octogrid[y][x] > 9 && gp !in flashed) {
                            newFlashes.add(gp)
                            gp.neighbours(octogrid[y].size, octogrid.size).forEach {
                                octogrid[it.y][it.x]++
                            }
                        }
                    }
                }
                flashed.addAll(newFlashes)
            } while(newFlashes.isNotEmpty())
            totalFlashes += flashed.size
            flashed.forEach { octogrid[it.y][it.x] = 0 }
        }
        println("Puzzle 1: " + totalFlashes)
    }
    fun part_2() {
        val totalOctos = octogrid.flatten().size
        var step = 0
        do {
            step++
            val flashed = mutableListOf<GridPoint>()
            for (y in octogrid.indices) {
                for (x in octogrid[y].indices) {
                    octogrid[y][x]++
                }
            }
            do {
                val newFlashes = mutableListOf<GridPoint>()
                for (y in octogrid.indices) {
                    for (x in octogrid[y].indices) {
                        val gp = GridPoint(x, y)
                        if (octogrid[y][x] > 9 && gp !in flashed) {
                            newFlashes.add(gp)
                            gp.neighbours(octogrid[y].size, octogrid.size).forEach {
                                octogrid[it.y][it.x]++
                            }
                        }
                    }
                }
                flashed.addAll(newFlashes)
            } while(newFlashes.isNotEmpty())
            flashed.forEach { octogrid[it.y][it.x] = 0 }
        } while(flashed.size != totalOctos)

        println("Puzzle 2: " + step)
    }
}