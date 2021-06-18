import socketio
import RPi.GPIO as GPIO

#INSTACE
sio = socketio.Client()

#PROPERTIES
HOST = ''

QUERY = {
    'idRoom': '',
    'status': ''
}

AIR_TYPE_DEVICE = ''
BULB_TYPE_DEVICE = ''

#GPIO'S
BULB = 12
AIR_CONDITIONING = 7

# NAME SOCKETS
QUERY_CLIENT = ''
GET_DEVICES_BY_ROOM = ''

# THROW EVENT WHEN OCURRED A CONNECTION WITH THE SERVER
@sio.event
def connect():
    print('Connection successfully')
    sio.emit(QUERY_CLIENT, QUERY)
    
# THROW EVENT WHEN OCURRED A ERROR WITH CONNECTION
@sio.event
def connect_error():
    print('The connection failed!')
    
# GET DEVICES BY ROOM
@sio.on(GET_DEVICES_BY_ROOM)
def on_devices(data):
    print('Data received', data)
    loop_data_received(data)

# LOOP DATA RECEIVED
def loop_data_received(data):
    for x in data['data']:
        value = x['value']
        
        if x['idTypeDevice'] == AIR_TYPE_DEVICE:
            print('Value AIR: ' + str(value))
            check_value_air(value)
            
        if x['idTypeDevice'] == BULB_TYPE_DEVICE:
            print('Value BULB: ' + str(value))
            check_value_bulb(value)
            
# CHECK VALUE AIR
def check_value_air(value):
    GPIO.output(AIR_CONDITIONING, value)

# CHECK VALUE BULB
def check_value_bulb(value):
    GPIO.output(BULB, value)
    
# INIT CONFIGURATION
def init_configuration():
    GPIO.setwarnings(False)
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(BULB, GPIO.OUT)
    GPIO.setup(AIR_CONDITIONING, GPIO.OUT)
    
# MAIN METHOD
def main():
    init_configuration()
    sio.connect(HOST)
    
if __name__ == '__main__':
    main()