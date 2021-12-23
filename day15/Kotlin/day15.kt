import java.io.*
import java.util.*
fun print_day_15() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 15" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Chiton -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_15()
    Day15().part_1()
    Day15().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day15 {
    data class Node(val x:Int = 0, val y:Int = 0, val dist: Int = 0)

    fun part_1() {

        val grid = File("../Input/day15.txt").readLines().map { it.toCharArray().map{ it.digitToInt() } }
        print("Puzzle 1: ")
        findShortestPath(grid)
    }

    private fun findShortestPath(grid: List<List<Int>>) {
        val pathways =  Array(grid.size) { Array(grid[0].size) { Int.MAX_VALUE } }
        val queue = PriorityQueue<Node> { nodeA, nodeB -> nodeA.dist - nodeB.dist } 

        pathways[0][0] = 0
        queue.add(Node(0,0, 0))

        while(queue.isNotEmpty()) {
            val (x, y, dist) = queue.poll()
            listOf(x to y + 1, x to y - 1, x + 1 to y, x - 1 to y).forEach { (X, Y) ->
                if (X in grid.indices && Y in grid[0].indices && pathways[X][Y] > dist + grid[X][Y]) {
                    pathways[X][Y] = dist + grid[X][Y]
                    queue.add(Node(X, Y, pathways[X][Y]))
                }
            }
        }
        println(pathways.last().last())
    }


    fun part_2() {
        val input = File("../Input/day15.txt").readLines()
        val totalY = input.size
        val totalX = input.first().length

        val grid = (0 until totalY * 5).map { y ->
            (0 until totalX * 5).map { x ->
                val baseNum = input[y % totalY][x % totalX].digitToInt()
                val tileDistance = (x/totalX) + (y/totalY)
                if (baseNum + tileDistance < 10) baseNum + tileDistance else (baseNum + tileDistance) - 9
            }
        }
        print("Puzzle 2: ")
        findShortestPath(grid)
    }
}