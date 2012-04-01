# coding:utf-8
require "test/unit"
require_relative "guess"

class TestGuess < Test::Unit::TestCase
  def setup
    test_string = "本日は晴天なり"
    @codings = ["sjis", "utf-8", "euc-jp"].map do |name|
      Encoding.find(name)
    end
    @strings = @codings.map do |coding|
      test_string.encode(coding).force_encoding(Encoding::ASCII_8BIT)
    end
  end

  def test_string_guess_encoding
    assert_equal(@codings, @strings.map {|str| str.guess_encoding})
  end

  def test_string_guess
    guessed_table = @strings.map do |str|
      str.dup.guess!
    end

    assert_equal(@codings, @strings.map {|str| str.guess.encoding})
    assert_equal(@codings, guessed_table.map {|str| str.encoding})
    assert(@strings.all? {|str| str.encoding == Encoding::ASCII_8BIT})
  end

  def test_io_guess_open
    default_external = Encoding.default_external
    Encoding.default_external = Encoding::ASCII_8BIT

    begin
      io = nil
      open("README.md") do |f|
        assert_equal(Encoding::ASCII_8BIT, f.external_encoding)
      end
      guess_open("README.md") do |f|
        io = f
        assert_equal(Encoding::UTF_8, f.external_encoding)
      end
      assert(io.closed?)
      guess_open("README.md", :encoding => Encoding::US_ASCII) do |f|
        assert_equal(Encoding::UTF_8, f.external_encoding)
      end
      guess_open("README.md", :external_encoding => Encoding::US_ASCII) do |f|
        assert_equal(Encoding::UTF_8, f.external_encoding)
      end
      assert_raise(ArgumentError) do
        guess_open("README.md", "r:SJIS") {}
      end
    ensure
      Encoding.default_external = default_external
    end
  end
end
