import asyncio
from bleak import BleakClient, BleakGATTCharacteristic

char_uuid = "00000007-0000-3512-2118-0009af100700"

async def callback(sender: BleakGATTCharacteristic, data: bytearray):
    print(f"{sender}: {data}")

async def connect():
    address = "D0:4E:AD:C0:AF:7D"
    async with BleakClient(address) as client:
        await client.start_notify(char_uuid, callback)
        await asyncio.sleep(10) 
        await client.stop_notify(char_uuid)

asyncio.run(connect())
