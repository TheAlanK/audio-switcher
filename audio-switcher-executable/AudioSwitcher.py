import subprocess
import os
import sys
import keyboard
import logging
from pystray import Icon as icon, Menu as menu, MenuItem as item
from PIL import Image, ImageDraw

logging.basicConfig(filename='AudioSwitcher.log', level=logging.DEBUG)

def create_image():
    # Create an image for the icon
    image = Image.new('RGB', (64, 64), color=(0, 0, 0))
    d = ImageDraw.Draw(image)
    d.rectangle([20, 20, 44, 44], fill=(255, 255, 255))
    return image

def on_exit(icon, item):
    icon.stop()
    os._exit(0)

if getattr(sys, 'frozen', False):
    script_dir = sys._MEIPASS
else:
    script_dir = os.path.dirname(os.path.abspath(__file__))

executable_path = os.path.join(script_dir, 'dependencies', 'audio-switcher.exe')

def run_executable():
    if os.path.exists(executable_path):
        logging.info(f"Running executable: {executable_path}")
        subprocess.run(executable_path, check=True, creationflags=subprocess.CREATE_NO_WINDOW)
    else:
        logging.error(f"Executable not found at {executable_path}")

keyboard.add_hotkey('ctrl+alt+a', run_executable)

# Setup system tray icon
icon('AudioSwitcher', create_image(), menu=menu(item('Exit', on_exit))).run()
