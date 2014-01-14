
var member = [];
var count = 0;
var net = require('net');
var server = net.createServer(function(socket){ //'connection' listener
  var name;
  var room;
  if(count === 0){
    socket.write("yes.");
    count++;
    // return;
  }
  else if(count === 1){
    socket.write("no.")
    // count = 0;
    // return;
  }
  console.log('client connected');
	socket.on('data', function (msg_sent){
    if (typeof(name) === 'undefined'){
      if(msg_sent.toString().trim().length > 3){
        name = msg_sent.toString().charAt(1);
        member[name] = socket;
        if(typeof(room) === 'undefined'){
          room = msg_sent.toString().charAt(0);
          member[name].room = room;
        }
        console.log('data :', msg_sent.toString());
      }
      return;
    }
    else {
      var namess = msg_sent.toString().charAt(0);
      var roomCurrent = msg_sent.toString().charAt(0);
      // for (var x in member){
      //    alert(member[x]);
      //    if(member[x].room === roomCurrent)
      //    {
      //       member[x].write(msg_sent.toString());
      //    }
      // }
      console.log('dataName :', namess);
      if (typeof(member[namess]) === 'undefined'){
        socket.write(namess + ' is offline now!');
      }
      else {
        console.log(msg_sent.toString());
        member[namess].write(msg_sent.toString());
      }
    }
  });

  socket.on('end', function() {
    console.log('client disconnected');
  });
  // c.write('hello\n');
  // c.pipe(c);
});
server.listen(8080, function() { //'listening' listener
  console.log('server start');
});