#!/usr/bin/env rake
require "bundler/gem_tasks"

task :default do
  Dir.chdir "ext"
  system("ruby extconf.rb") if !File.exist?("Makefile")
  system("make")
  Dir.chdir ".."
end

task :test => [:default] do
  $:.unshift "./ext"
  load "test/test_guess4r.rb"
end
