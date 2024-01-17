import asyncio
from bleak import BleakClient

async def enable_notifications(address, service_uuid, char_uuid):
    async with BleakClient(address) as client:
        await client.start_notify(char_uuid, notification_callback)
        await asyncio.sleep(60)  # Run for 60 seconds (adjust as needed)

async def notification_callback(sender: int, data: bytearray):
    print(f"Received data from {sender}: {data}")

# Replace with the actual service and characteristic UUIDs
service_uuid = "0000180d-0000-1000-8000-00805f9b34fb"  # Heart Rate service
char_uuid = "00002a39-0000-1000-8000-00805f9b34fb"    # Heart Rate Measurement characteristic
device_address = "D0:4E:AD:C0:AF:7D"  # Replace with your device's address

asyncio.run(enable_notifications(device_address, service_uuid, char_uuid))
