object pf {
  val md = java.security.MessageDigest.getInstance("sha-1")

  def getdigest(str: String): String =
    md.digest(str.getBytes("utf-8")).map("%02x".format(_)).mkString

  def readsource(): String = {
    val filename = getfilename()
    scala.io.Source.fromFile(filename).mkString
  }

  def getfilename(): String =
    Thread.currentThread.getStackTrace()(3).getFileName()

  def printflag(flag: String) =
    println("STCTF#" + flag + "#")

  def generateflagvalue(): String = {
    val source = readsource()
    val sourcedigest = getdigest(source)
    assert(sourcedigest.length == 40)
    val salt = 42
    val tempvalue = getdigest(salt.toString() + sourcedigest)
    tempvalue match {
      case x if x.startsWith("aa") => "don't think so"
      case y if y.endsWith("cc") => "no, thank you"
      case z if z.contains("26018") => getdigest(z).substring(10, 22)
      case _ => "really ?"
    }
  }

  def main(args: Array[String]) = {
    val flagvalue = generateflagvalue()
    if (flagvalue.contains(' '))
      println("invalid flag")
    else
      printflag(flagvalue)
  }
}
