#
# mruby on YABM script
#
# m2x update script
#

DEVICE_ID = "naisyo"
PRIMARY_API_KEY = "naisyo"

STREAM_ID = "temperature"
INTERVAL = 10

def delay(yabm, val) 
  start = yabm.count() 
  while yabm.count() < start + val do
  end
end

begin

yabm = YABM.new

# net setup

yabm.netstartdhcp

yabm.print yabm.getaddress + "\n"

count = 0

while 1 do
  yabm.print "."
  count = count + 1
  yabm.print " " + count.to_s

  body='{ "value": ' + count.to_s + ' }'

  header = Hash.new
  header.store('User-Agent', "test-agent")
  header.store('X-M2X-KEY', PRIMARY_API_KEY)
  header.store('Content-Type', "application/json")
  header.store('Body', body)
  path = "/v2/devices/" + DEVICE_ID + "/streams/" + STREAM_ID + "/value"
  res = SimpleHttp.new("http", "api-m2x.att.com", 80).put(path, header)
  if res 
    yabm.print " " + res.status.to_s
  end
  yabm.print "\n"
  delay(yabm, INTERVAL * 1000)
end

rescue => e
  yabm.print e.to_s
end
