import os
import qrcode

img = qrcode.make("https://youtub.e/xvFZjo5PgG0")

img.save("qr.png", "PNG")
