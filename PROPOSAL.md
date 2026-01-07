# Final Project Proposal
  
## Group Members:
  
Matvei Karp
       
# Intentions:
  
Multi-user chat
    
# Intended usage:
  
Terminal based client, allowing user to send messages to the server and through it to all other users and allowing user to see all messages sent by others. Ideally with several "rooms" where the user can select which room to send to when connecting.
  
# Technical Details:
  
Processes (forking) + sockets + select for the server connection
  
Structure:
    main server (handles users connecting)
    |
    room server (in case there are multiple rooms, a separate server will be forked to handle each room, with users being passed over after initial handshake, based on the user sending the main server the name of the room they want to connect to)
    
    user - performs handshake, sends over room details (hopefully), sends over "username" to display, sends over messages. recieves and displays other users' messages from server
    

    
# Intended pacing:

timeline:
    
    stage one:
        single room, main + room server combined in one, with the ability to connect to clients and share their messages
  
        sub stage 1: handshake - jan 8
        sub stage 2: sharing messages - jan 10
        sub stage 3: passable appearance - jan 12
            
    stage two:
        split main server from room server, introducing multi room system - jan 15