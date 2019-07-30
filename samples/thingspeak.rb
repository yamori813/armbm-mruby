#
# mruby on YABM script
#
# thingspeak channel update 
#

APIKEY = "naisyo"
INTERVAL = 20

def delay(yabm, val) 
  start = yabm.count() 
  while yabm.count() < start + val do
  end
end

begin

# ip address setting

LED = 7

yabm = YABM.new

yabm.gpiosetdir(1 << LED)

yabm.gpiosetdat(1 << LED)

yabm.netstartdhcp

# sync date by ntp use https X.509
ntpaddr = rtl.lookup("ntp.nict.jp")
rtl.sntp(ntpaddr)

ip = yabm.getaddress

yabm.print ip + "\n"

count = 0

while 1 do
  yabm.print "."
  count = count + 1
  yabm.print " " + count.to_s
  yabm.gpiosetdat(0)
  res = SimpleHttp.new("https", "api.thingspeak.com", 443).request("GET", "/update?api_key=" + APIKEY + "&field1="+count.to_s, {'User-Agent' => "test-agent"})
  yabm.gpiosetdat(1 << LED)
  if res && res.body
    yabm.print " " + res.body + "\n"
  else
    yabm.print " error\n"
  end
  delay(yabm, INTERVAL * 1000)
end

rescue => e
  yabm.print e.to_s
end
