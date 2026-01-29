from manim import *
from random import uniform


def RayCast():
    caca = 1



class Test(ZoomedScene):
    def construct(self):
        fov_tracker = ValueTracker(60)

        fov_result = ValueTracker(
            np.tan(fov_tracker.get_value() * PI / 180 / 2)
        )
        fov_result.add_updater(
            lambda t: t.set_value(
                np.tan(fov_tracker.get_value() * PI / 180 / 2))
        )

        result_text = always_redraw(
            lambda: MathTex(
                f"fov({fov_tracker.get_value():.0f}) = {fov_result.get_value():.2f} =",
                r"\tan\left(\frac{\text{fov}\cdot\pi}{180 \cdot 2}\right)",
            )
        )

        self.add(fov_result, result_text, fov_result)
        self.play(fov_tracker.animate.set_value(
            160), run_time=5, rate_func=linear)
        self.wait()

        return
        fov_text_r = VGroup()
        camera_l.set_value(tan(fov_deg.get_value() * PI / 180 / 2))
        self.play(Transform(fov_text, fov_text_r))
        camera = always_redraw(Vector([camera_l.get_value(), 0]))

        return
        plane = NumberPlane(x_range=[-20, 20],
                            y_range=[-20, 20]).add_coordinates()
        self.camera.frame.scale(0.5)
        test = Vector(camera.get_vector() + direction.get_vector())
        self.add(plane)
        self.play(FadeIn(player))
        self.play(GrowArrow(direction.set_z_index(0)))
        self.wait()


class Testing(MovingCameraScene):
    def construct(self):
        player = Dot(radius=0.1, color=PURE_RED)
        plane = NumberPlane(y_range=[-30, 30],
                            x_range=[-30, 30]).add_coordinates()
        label = MathTex(f"({player.get_x()},{player.get_y()})").scale(0.5)
        coord_text = 
        bg = SurroundingRectangle(coord_text, color=WHITE, buff=0.3, fill_color=BLACK,
                                  fill_opacity=1, corner_radius=0.2, stroke_width=3)
        panel = VGroup(bg, coord_text)

        def update_pos_label(label: MathTex):
            new_label = MathTex(
                f"({player.get_x():.2f},{player.get_y():.2f})").scale(0.8)
            new_label.next_to(player, UP, buff=0.2)
            label.become(new_label)

        def update_panel(panel: VGroup):

            panel.scale_to_fit_height(self.camera.frame.height * 0.15)
            scale_factor = self.camera.frame.height / 8.0
            buff = 0.3 * scale_factor
            panel.move_to(
                self.camera.frame.get_corner(DR) +
                LEFT * (panel.width / 2 + buff) +
                UP * (panel.height / 2 + buff))

        panel.add_updater(update_panel)
        label.add_updater(update_pos_label)
        self.camera.frame.scale(2)
        self.add(plane)
        player_anim = [
            FadeIn(player, run_time=2),
            Flash(player, num_lines=10, color=PURE_RED),
            DrawBorderThenFill(panel),
        ]
        animations = [
            self.camera.frame.animate(run_time=5).scale(0.3),
            LaggedStart(*player_anim, lag_ratio=0.5),
        ]
        self.play(AnimationGroup(*animations, lag_ratio=0.3))

        self.wait()
        self.wait()

        for _ in range(5, 10):
            if _ < 3:
                x_val = uniform(-5.0, 5.0)
                y_val = uniform(-5.0, 5.0)
                target_pos = plane.c2p(x_val, y_val)
                self.play(
                    player.animate.move_to(target_pos),
                    self.camera.frame.animate.move_to(target_pos),
                    run_time=2
                )
            elif _ == 6:
                x_val = uniform(-5.0, 5.0)
                y_val = uniform(-5.0, 5.0)
                target_pos = plane.c2p(x_val, y_val)
                self.add(label)
                self.play(
                    player.animate.move_to(target_pos),
                    self.camera.frame.animate.move_to(target_pos),
                    run_time=2
                )
            else:
                x_val = uniform(-5.0, 5.0)
                y_val = uniform(-5.0, 5.0)
                target_pos = plane.c2p(x_val, y_val)
                self.play(
                    player.animate.move_to(target_pos),
                    self.camera.frame.animate.move_to(target_pos),
                    run_time=2
                )
        target_pos = plane.c2p(0, 0)
        self.play(
            player.animate.move_to(target_pos),
            self.camera.frame.animate.move_to(target_pos),
            run_time=2
        )
        self.wait()
