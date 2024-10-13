import pytwin

pytwin.init()

while pytwin.isRunning():
    pytwin.drawCall(
        pytwin.DrawCallType.DRAW_CLEAR, pytwin.DrawCallMode.TRIANGLE_MODE
    )
    pytwin.pollEvents()

    pytwin.render()
