from random import uniform
from manim import *











def RayCast():
    caca = 1


class Testing(MovingCameraScene):
    def construct(self):
        player = Player(0, 0)
        panel = Panel(player)
        panel.scale(0.8)
        self.add(plane)
        self.add(player)
        self.add(panel)
        frame = self.camera.frame
        x_val = 0
        y_val = 0

        def pin_panel(mob):
            corner = self.camera.frame.get_corner(DR)
            mob.move_to(
                corner
                + LEFT * (mob.width / 2 + 0.3)
                + UP * (mob.height / 2 + 0.3)
            )

        panel.add_updater(pin_panel)

        

        self.wait()

        for _ in range(0, 10):
            x_val = uniform(-5.0, 5.0)
            y_val = uniform(-5.0, 5.0)
            target_pos = plane.c2p(x_val, y_val)
            if _ < 3:
                self.play(player.x.animate.set_value(x_val),
                          player.y.animate.set_value(y_val),
                          frame.animate.move_to(target_pos),
                          run_time=2)
            elif _ == 6:
                self.play(player.x.animate.set_value(x_val),
                          player.y.animate.set_value(y_val),
                          frame.animate.move_to(target_pos),
                          run_time=2)
            else:
                self.play(player.x.animate.set_value(x_val),
                          player.y.animate.set_value(y_val),
                          frame.animate.move_to(target_pos),
                          run_time=2)
        self.play(player.x.animate.set_value(x_val),
                  player.y.animate.set_value(y_val),
                  frame.animate.move_to(target_pos),
                  run_time=2)
        self.wait()
        self.play(camera)
