Import("env")

board_config = env.BoardConfig()

board_config.update("name", "WootPad")
board_config.update("vendor", "spookybear0")
board_config.update("build.usb_product", "WootPad")
board_config.update("build.hwids", [
    ["0xc007","0x0001"]
])
