# coding:utf-8
require_relative "guess"

ary = ["sjis", "utf-8", "euc-jp"].map do |coding|
  "本日は晴天なり".encode(coding).force_encoding(Encoding::ASCII_8BIT)
end

ary.each do |str|
  p str.guess.encoding
  p str.encoding
  str.guess!
  p str.encoding
end
