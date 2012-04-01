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
end
