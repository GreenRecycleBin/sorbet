# typed: false
class C
  def self.method1
# ^^^ error: Hint: this "def" token might not be properly closed

  sig {void}
  def self.method2
  end
end # error: unexpected token "end of file"
