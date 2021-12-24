import java.io.*
fun print_day_22() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 22" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Reactor Reboot -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_22()
    Day22().part1()
    Day22().part2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

fun String.toRange(): IntRange = this.split("..").let { IntRange(it[0].toInt(), it[1].toInt()) }

class Day22 {
    fun String.toRange(): IntRange = this.split("..").let { IntRange(it[0].toInt(), it[1].toInt()) }

    data class Point3D(val x: Int, val y: Int, val z: Int)
    data class Cube(val xAxis: IntRange, val yAxis: IntRange, val zAxis: IntRange) {
        fun cubicVolume() = 1L * this.xAxis.count() * this.yAxis.count() * this.zAxis.count()
        fun overlaps(that: Cube) =
                (this.xAxis.first <= that.xAxis.last && this.xAxis.last >= that.xAxis.first) &&
                        (this.yAxis.first <= that.yAxis.last &&
                                this.yAxis.last >= that.yAxis.first) &&
                        (this.zAxis.first <= that.zAxis.last && this.zAxis.last >= that.zAxis.first)
        fun intersect(that: Cube) =
                if (!overlaps(that)) null
                else
                        Cube(
                                maxOf(this.xAxis.first, that.xAxis.first)..minOf(
                                                this.xAxis.last,
                                                that.xAxis.last
                                        ),
                                maxOf(this.yAxis.first, that.yAxis.first)..minOf(
                                                this.yAxis.last,
                                                that.yAxis.last
                                        ),
                                maxOf(this.zAxis.first, that.zAxis.first)..minOf(
                                                this.zAxis.last,
                                                that.zAxis.last
                                        )
                        )
    }
    data class Cuboid(val cube: Cube, val on: Boolean) {
        fun intersect(other: Cuboid) =
                if (this.cube.overlaps(other.cube)) Cuboid(this.cube.intersect(other.cube)!!, !on)
                else null
    }

    private val cubes =
            File("../Input/day22.txt").readLines().map {
                val on = it.split(" ").first() == "on"
                val cube =
                        it.split(" ").last().split(",").let {
                            Cube(
                                    it[0].drop(2).toRange(),
                                    it[1].drop(2).toRange(),
                                    it[2].drop(2).toRange()
                            )
                        }
                Cuboid(cube, on)
            }

    fun part1() {
        val region = Cube(-50..50, -50..50, -50..50)
        val onCubes = mutableSetOf<Point3D>()
        cubes.forEach {
            val (cube, on) = it
            if (cube.overlaps(region)) {
                cube.xAxis.forEach { x ->
                    cube.yAxis.forEach { y ->
                        cube.zAxis.forEach { z ->
                            if (on) onCubes.add(Point3D(x, y, z))
                            else onCubes.remove(Point3D(x, y, z))
                        }
                    }
                }
            }
        }

        println("Puzzle 1: " + onCubes.size)
    }

    fun part2() {
        fun findIntersections(a: Cube, b: Cube): Cube? = if (a.overlaps(b)) a.intersect(b) else null
        val volumes = mutableListOf<Cuboid>()

        cubes.forEach { cube ->
            volumes.addAll(
                    volumes.mapNotNull { other ->
                        findIntersections(cube.cube, other.cube)?.let { Cuboid(it, !other.on) }
                    }
            )
            if (cube.on) volumes.add(cube)
        }

        println("Puzzle 2: " + volumes.sumOf { it.cube.cubicVolume() * (if (it.on) 1 else -1) })
    }
}
