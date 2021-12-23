import java.io.*
fun print_day_17() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 17" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Trick Shot -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}

fun main() {
    print_day_17() 
    println("Puzzle 1: ${Day17().puzzle1()}")
    println("Puzzle 2: ${Day17().puzzle2()}")
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day17 {

    data class BoundingBox(val xRange: IntRange, val yRange: IntRange)
    private val target = File("../Input/day17.txt").readLines().first().drop(13)
        .split(", ").map { it.drop(2).split("..").let { (a, b) -> a.toInt()..b.toInt() }}
        .let { BoundingBox(it[0], it[1]) }


    fun puzzle1() = (1..400).flatMap { x -> (1..400).map { y -> checkStep(x, y, target) } }.fold(0) { max, step -> if (step.first) maxOf(max, step.second) else max }
    fun puzzle2() = (1..400).flatMap { x -> (-400..400).map { y -> checkStep(x, y, target).first } }.count { it }


    data class Coord(var x:Int, var y:Int)
    data class Velocity(var x:Int, var y:Int)
    private fun checkStep(xVelocity: Int, yVelocity: Int, target: BoundingBox): Pair<Boolean, Int> {
        val p = Coord(0, 0)
        val v = Velocity(xVelocity, yVelocity)
        var maxHeight = 0
        var hitTarget = false
        while (p.x <= target.xRange.last && p.y >= target.yRange.first) {
            p.x += v.x     
            p.y += v.y

            maxHeight = maxOf(p.y, maxHeight)
            if (p.x in target.xRange && p.y in target.yRange) {
                hitTarget = true
                break 
            }

            if (v.x > 0) v.x--
            v.y--
        }
        return Pair(hitTarget, maxHeight)
    }
}