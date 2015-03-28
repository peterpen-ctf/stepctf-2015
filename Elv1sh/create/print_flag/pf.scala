
object Pf {
  val md = java.security.MessageDigest.getInstance("SHA-1")

  def getDigest(str: String): String =
    md.digest(str.getBytes("UTF-8")).map("%02x".format(_)).mkString

  def readSource(): String = {
    val filename = getFilename()
    scala.io.Source.fromFile(filename).mkString
  }

  def getFilename(): String = 
    Thread.currentThread.getStackTrace()(3).getFileName()

  def printFlag(suffix: String) = 
    println("STCTF#" + suffix)

  def generateFlagValue(): String = {
    val source = readSource()
    val sourceDigest = getDigest(source)
    assert(sourceDigest.length == 40)
    val salt = 42
    val tempValue = getDigest(salt.toString() + sourceDigest)
    tempValue match  {
      case x if x.startsWith("a") => "don't think so"
      case y if y.endsWith("8") => "no, thank you"
      case z if z.contains("b2") => getDigest(z).substring(10, 22)
      case _  => "really?"
    }
  }

  def main(args: Array[String]) = {
    val flagValue = generateFlagValue()
    printFlag(flagValue)
  }
}

