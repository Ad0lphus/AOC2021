import java.io.*
fun print_day_20() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 20" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Trench Map -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}

fun main() {
    print_day_20()
    print("Puzzle 1: ")
    Day20().solve(2)
    print("Puzzle 2: ")
    Day20().solve(50)
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

@OptIn(ExperimentalStdlibApi::class)
class Day20 {
    data class Point(val x:Int, val y:Int)

    private val rawData = File("../Input/day20.txt").readLines()

    private val algorithm = rawData.first()
    var pixels = buildMap<Point, Boolean> {
        rawData.drop(2).forEachIndexed { y, str ->  str.forEachIndexed { x, c -> put(Point(x, y), c == '#') } }
    }.toMutableMap()


    fun getPixelAt(x:Int, y:Int, flip:Boolean = false) = pixels[Point(x, y)] ?: flip 
    fun getEnhancePixel(centreX:Int, centreY:Int, flip:Boolean): Boolean {
        val binary = StringBuilder()
        for (y in centreY-1 .. centreY+1) {
            for (x in centreX-1 .. centreX+1) {
                binary.append( if (getPixelAt(x, y, flip)) '1' else '0' )
            }
        }
        return algorithm[binary.toString().toInt(2)] == '#'
    }

    fun printImage() {
        val xAxis = pixels.keys.minOf { it.x } .. pixels.keys.maxOf { it.x }
        val yAxis = pixels.keys.minOf { it.y } .. pixels.keys.maxOf { it.y }

        for (y in yAxis) {
            println()
            for (x in xAxis) print(if (getPixelAt(x, y)) "#" else ".")
        }
    }

    fun solve(steps: Int) {
        repeat(steps) {
            val minX = pixels.keys.minOf { it.x } - 1
            val maxX = pixels.keys.maxOf { it.x } + 1
            val minY = pixels.keys.minOf { it.y } - 1
            val maxY = pixels.keys.maxOf { it.y } + 1

            val newImage = mutableMapOf<Point, Boolean>()
            for (y in minY..maxY) {
                for (x in minX..maxX) {
                    newImage[Point(x, y)] = getEnhancePixel(x, y, it % 2 == 1)
                }
            }
            pixels = newImage
        }

        println(pixels.count { it.value })
    }
}