#
# Sample script for mruby on Yet Another Bare Metal
#

begin

yabm = YABM.new

yabm.print "Hello Bear Metal mruby on YABM"

yabm.watchdogstart(30)

while 1 do
   yabm.print "."
   start = yabm.count() 
   while yabm.count() < start + 500 do
   end
   yabm.watchdogreset
end

rescue => e
  yabm.print e.to_s
end
