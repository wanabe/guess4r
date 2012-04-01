# -*- encoding: utf-8 -*-

Gem::Specification.new do |gem|
  gem.authors       = ["wanabe"]
  gem.email         = ["s.wanabe@gmail.com"]
  gem.description   = "libguess binding for ruby 1.9 or later."
  gem.summary       = "libguess binding for ruby 1.9 or later."
  gem.homepage      = ""

  gem.files         = `git ls-files`.split($\)
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.name          = "guess4r"
  gem.require_paths = ["ext"]
  gem.version       = "0.0.1.20120401"
  gem.extensions << "ext/extconf.rb"

end
