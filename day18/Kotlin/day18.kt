import java.io.*
fun print_day_18() {
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 18" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Snailfish -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)
    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}

fun main() {
    print_day_18()
    println("Puzzle 1: " + Day18().part_1())
    println("Puzzle 2: " + Day18().part_2())
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day18 {
    private val input = File("../Input/day18.txt").readLines()
    fun part_1() = input.map { parse(it) }.reduce { a, b -> a + b }.magnitude()
    fun part_2() = input.indices.flatMap { i -> input.indices.map { j -> i to j}}.filter {(i,j) -> i != j }.maxOf { (i,j) -> (parse(input[i]) + parse(input[j])).magnitude() }

    private fun parse(input: String): Num {
        var cur = 0

        fun _parse(): Num =
            if (input[cur] == '[') {
                cur++
                val left = _parse()
                cur++ 
                val right = _parse()
                cur++ 
                Num.NumPair(left, right)
            }
            else Num.NumValue(input[cur].digitToInt()).also { cur++ }

        return _parse()
    }


    sealed class Num {
        var parent: NumPair? = null

        class NumValue(var value: Int) : Num() {
            override fun toString(): String = value.toString()

            fun canSplit(): Boolean = value >= 10
            fun split() {
                val num = NumPair(NumValue(value / 2), NumValue((value + 1) / 2))
                parent?.replaceWith(this, num)
            }
        }
        class NumPair(var left: Num, var right: Num) : Num() {
            init {
                left.parent = this
                right.parent = this
            }
            override fun toString(): String = "[$left,$right]"

            fun explode() {
                val x = if (left is NumValue) (left as NumValue).value else null
                val y = if (right is NumValue) (right as NumValue).value else null
                findValueToLeft()?.let { it.value += x!! }
                findValueToRight()?.let { it.value += y!! }
                parent?.replaceWith(this, NumValue(0))
            }

            fun replaceWith(child: Num, newValue: Num) {
                if (left == child)      { left = newValue  }
                else if (right == child){ right = newValue }

                newValue.parent = this
            }
        }


        fun magnitude(): Int = when(this) {
            is NumValue -> value
            is NumPair -> left.magnitude() * 3 + right.magnitude() * 2
        }

        operator fun plus(other: Num): Num =
            NumPair(this, other).apply {
                left.parent = this
                right.parent = this
                reduce()
            }

        fun reduce() {
            do  {
                var exploded = false
                var split = false

                findNextExplode()?.apply {
                    explode()
                    exploded = true
                }
                if (!exploded) findNextToSplit()?.apply {
                    split()
                    split = true
                }
            } while (exploded || split)
        }

        fun findValueToRight(): NumValue? {
            if (this is NumValue) return this
            if (this == parent?.left) return parent!!.right.findValueFurthestLeft()
            if (this == parent?.right) return parent!!.findValueToRight()

            return null
        }
        fun findValueToLeft(): NumValue? {
            if (this is NumValue) return this
            if (this == parent?.left) return parent!!.findValueToLeft()
            if (this == parent?.right) return parent!!.left.findValueFurthestRight()

            return null
        }
        private fun findValueFurthestLeft(): NumValue? = when(this) {
            is NumValue -> this
            is NumPair -> this.left.findValueFurthestLeft()
        }
        private fun findValueFurthestRight(): NumValue? = when(this) {
            is NumValue -> this
            is NumPair -> this.right.findValueFurthestRight()
        }

        private fun findNextToSplit(): NumValue? =
            if (this is NumValue && canSplit()) this
            else if (this is NumPair) left.findNextToSplit() ?: right.findNextToSplit()
            else null

        private fun findNextExplode(depth: Int = 0): NumPair? =
            if (this is NumPair) {
                if (depth >= 4) this
                else left.findNextExplode(depth + 1) ?: right.findNextExplode(depth + 1)
            }
            else null
    }
}