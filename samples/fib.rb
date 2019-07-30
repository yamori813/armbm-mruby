#
# mruby on YABM script
#
# Fibonacci number script use by netconsole

def fib n
  return n if n < 2
  fib(n-2) + fib(n-1)
end

begin

yabm = YABM.new

addr = "10.10.10.123"
mask = "255.255.255.0"
gw = "10.10.10.3"
dns = "10.10.10.3"

yabm.netstart(addr, mask, gw, dns)

dist = "10.10.10.3"

yabm.udpinit

while 1 do
   yabm.print "."
   yabm.udpsend(dist, 6666, ".", 1)
   start = yabm.count() 
   fib(32)
   time = (yabm.count() - start) / 1000
   res = "fib(32): " + time.to_s + "sec\n"
   yabm.udpsend(dist, 6666, res, res.length)
end

rescue => e
  yabm.udpsend(dist, 6666, e.to_s, e.to_s.length)
end
