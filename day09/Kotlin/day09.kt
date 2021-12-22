import java.io.*
fun print_day_9() {
    
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 9" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Smoke Basin -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)

    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_9()
    Day9().part_1()
    Day9().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day9 {

    data class Point(val x:Int, val y:Int) {
        fun neighbours(xBoundary: Int, yBoundary: Int): List<Point> =
            listOf(Point(x-1, y), Point(x+1, y), Point(x, y-1), Point(x, y+1) ).filter {
                it.x in 0 until xBoundary && it.y  in 0 until yBoundary
            }
    }

    val heightmap = File("../Input/day9.txt").readLines().map { it.toCharArray().map { c -> c.digitToInt() } }

    fun part_1() {
        val total = heightmap.foldIndexed(0) { yIndex, acc, list ->
            list.foldIndexed(acc) { xIndex, sum, height ->
                if (Point(xIndex, yIndex).neighbours(heightmap[0].size, heightmap.size).count { heightmap[it.y][it.x] <= height } == 0)
                    sum + heightmap[yIndex][xIndex] + 1
                else sum
            }
        }

        println("Puzzle 1: $total")
    }

    fun part_2() {

        fun getLowPoints() = heightmap.flatMapIndexed { yIndex, list ->
            list.mapIndexed { xIndex, height ->
                val smallerNeighbours = Point(xIndex, yIndex).neighbours(heightmap[0].size, heightmap.size).count { heightmap[it.y][it.x] <= height }
                if (smallerNeighbours == 0) Point(xIndex, yIndex) else null
            }.filterNotNull()
        }
        fun getBasinSize(p: Point): Int {
            val visited = mutableSetOf(p)
            val queue = mutableListOf(p)
            while (queue.isNotEmpty()) {
                val newNeighbors = queue.removeFirst()
                    .neighbours(heightmap[0].size, heightmap.size)
                    .filter { it !in visited }
                    .filter { heightmap[it.y][it.x] != 9 }
                visited.addAll(newNeighbors)
                queue.addAll(newNeighbors)
            }
            return visited.size
        }

        val answer = getLowPoints().map { getBasinSize(it) }
            .sortedDescending()
            .take(3)
            .reduce { total, next -> total * next }

        println("Puzzle 2: $answer")

    }
}