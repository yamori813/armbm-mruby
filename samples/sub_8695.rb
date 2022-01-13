#
# yabm mruby script
# KS8695 subroutine script
#

LED = 7

def gpioinit yabm
  yabm.gpiosetdir(1 << LED)

  yabm.gpiosetdat(1 << LED)
end

def ledon yabm
    yabm.gpiosetdat(0)
end

def ledoff yabm
  yabm.gpiosetdat(1 << LED)
end
