from manim import *


class Test(ZoomedScene):
    def construct(self):
        fov_deg = DecimalNumber(60)
        camera_l = ValueTracker(fov_deg.get_value())

        result_text = MathTex(
            f"{camera_l.get_value():.2f} =",
            r"\tan\left(\frac{\text{fov}\cdot\pi}{180 \cdot 2}\right)"
        )

        def update_result(text: MathTex):
            new = camera_l.get_value() * PI / 180 / 2
            text.set_text(f"{new} = " +
                          r"\tan\left(\frac{\text{fov}\cdot\pi}{180 \cdot 2}\right)")
        
        def update_nbr()
            

        result_text.add_updater(update_result)

        # self.play(FadeIn(result_text))
        self.add(fov_deg)
        self.play(fov_deg.animate.set_value(100), run_time=5)
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
