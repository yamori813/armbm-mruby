
MRuby::CrossBuild.new('kendin') do |conf|
  toolchain :gcc
  conf.cc.command = 'arm-none-eabi-gcc'
  conf.archiver.command = 'arm-none-eabi-ar'

  cc.defines << %w(MRB_NO_STDIO)
  cc.defines << %w(MRB_NO_FLOAT)
  cc.defines << %w(YABM_KEDEN)
  conf.cc.flags << "-mcpu=arm922t"
  conf.cc.include_paths = ["#{root}/include", "../build/work/newlib-3.0.0.20180831/newlib/libc/include"]

  conf.gem :github => 'yamori813/mruby-yabm'
  conf.gem :github => 'yamori813/mruby-simplehttp'
# use in mruby-simplehttp'
  conf.gem :core => "mruby-string-ext"

end
