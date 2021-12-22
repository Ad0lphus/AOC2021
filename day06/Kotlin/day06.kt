import java.io.*

fun print_day_6() {
    
    val yellow = "\u001B[33m"
    val reset = "\u001b[0m"
    val green = "\u001B[32m"
    println(yellow + "-".repeat(25) + "Advent of Code - Day 6" + "-".repeat(25) + reset)
    println(green)
    val process = Runtime.getRuntime().exec("figlet Lanternfish -c -f small")
    val reader = BufferedReader(InputStreamReader(process.inputStream))
    reader.forEachLine { println(it) }
    println(reset)

    println(yellow + "-".repeat(33) + "Output" + "-".repeat(33) + reset + "\n")
}
fun main() {
    print_day_6()
    Day6().puzzle1()
    Day6().puzzle2()
    println("\n" + "\u001B[33m" + "=".repeat(72) + "\u001b[0m" + "\n")
}

class Day6 {
    val fish = File("../Input/day6.txt").readLines().first().split(",").map{it.toInt()}.toMutableList()
    fun puzzle1() {
        for(i in 1..80) {
            val newFish = mutableListOf<Int>()
            for (idx in fish.indices) {
                if (fish[idx] == 0) {
                    fish[idx] = 6
                    newFish.add(8)
                }
                else {
                    fish[idx]--
                }
            }
            fish.addAll(newFish)
        }
        println("Puzzle 1: ${fish.size}")
    }
    fun puzzle2() {
        data class NewFish(var age: Int, val numNewFish:Long)
        val spawnedFish = mutableListOf<NewFish>()
        for(i in 1..256) {
            var newFish = 0L
            for (idx in fish.indices) {
                if (fish[idx] == 0) {
                    fish[idx] = 6
                    newFish++
                }
                else {
                    fish[idx]--
                }
            }
            for(spawned in spawnedFish) {
                if (spawned.age == 0) {
                    newFish += spawned.numNewFish
                    spawned.age = 6
                }
                else {
                    spawned.age--
                }
            }
            spawnedFish.add(NewFish(8, newFish))
        }
        val total = spawnedFish.sumOf { it.numNewFish } + fish.size
        println("Puzzle 2: $total")
    }

}