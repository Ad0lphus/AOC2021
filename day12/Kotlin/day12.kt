import java.io.*
fun print_day_12() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 12" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Passage Pathing -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_12()
    Day12().part_1()
    Day12().part_2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day12 {

    data class Node(val name: String, val isLarge: Boolean = false, var connections: List<Node> = mutableListOf())

    fun part_1() {
        val nodes = mutableMapOf<String, Node>()

        fun followPaths(node: Node, path: List<Node>): List<List<Node>> {
            val newPath = path+node
            return if (node.name == "end" || (path.contains(node) && !node.isLarge)) {
                listOf(newPath)
            } else {
                node.connections.flatMap {
                    followPaths(it, newPath)
                }
            }
        }

        File("../Input/day12.txt").readLines().forEach {
            val pathway = it.split("-").map { node ->
                if (!nodes.containsKey(node)) {
                    nodes[node] = Node(node, node.isUpperCase())
                }
                nodes[node]!!
            }

            pathway[0].connections += pathway[1]
            pathway[1].connections += pathway[0]
        }

        val start = nodes["start"]!!
        val paths = followPaths(start, listOf()).filter { it.last().name == "end" } // only keep nodes that actually end
        println("Puzzle 1: ${paths.size}")

    }
    fun part_2() {
        val nodes = HashMap<String, HashSet<String>>()

        File("../Input/day12.txt").readLines().forEach {
            val (a,b) = it.split("-")
            nodes.getOrPut(a) { HashSet() }.add(b)
            nodes.getOrPut(b) { HashSet() }.add(a)
        }

        fun canVisit(name: String, path: List<String>): Boolean =
            when {
                name.isUpperCase() -> true
                name == "start" -> false
                name !in path -> true
                else -> path.filterNot { it.isUpperCase() }.groupBy { it }.none { it.value.size == 2 }
            }

        fun followPaths(path: List<String> = listOf("start")): List<List<String>> =
            if (path.last() == "end") listOf(path)
            else nodes.getValue(path.last())
                .filter  { canVisit(it, path) }
                .flatMap { followPaths( path + it) }

        println("Puzzle 2: ${followPaths().size}")
    }
}

private fun String.isUpperCase(): Boolean = this == this.uppercase()