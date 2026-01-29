from manim import *
from random import uniform


class Panel(VGroup):
    def __init__(self, player: Player, scene: MovingCameraScene):
        super().__init__()
        self.content = VGroup(
            Dot(color=PURE_RED),
            MathTex("="),
            Text("player", font_size=24),
        ).arrange(RIGHT)
        self.box = always_redraw(lambda: SurroundingRectangle(
            self.content, color=WHITE, buff=0.3, fill_color=BLACK,
            fill_opacity=1, corner_radius=0.2, stroke_width=3
        ))
        self.add(self.box, self.content)

        self.add_updater(lambda m: m.move_to(scene.camera.frame.get_corner(DR) +
                                             LEFT * 1.5 +
                                             UP * 0.75))


class Plane(NumberPlane):
    def __init__(self):
        super().__init__(
            y_range=[-30, 30],
            x_range=[-30, 30])
        self.add_coordinates()


class Player(Dot):
    def __init__(self, x, y,):
        super().__init__(color=PURE_RED, radius=0.1)
        self.x = ValueTracker(x)
        self.y = ValueTracker(y)
        self.ray_x = ValueTracker(0)
        self.ray_y = ValueTracker(0)

        def player_update(player: Player):
            player.move_to(
                [player.x.get_value(), player.y.get_value(), 0])
        self.add_updater(player_update)

    def move(self, x, y) -> AnimationGroup:
        move_x = self.x.animate.set_value(x)
        move_y = self.y.animate.set_value(y)
        return AnimationGroup(move_x, move_y)


class FollowingCam:
    def __init__(self, camera: MovingCamera):
        self.camera = camera

    def move(self, x, y) -> Animation:
        return self.camera.frame.animate.move_to([x, y, 0])

    def zoom(self, zoom) -> Animation:
        return self.camera.frame.animate.scale(zoom)

    def move_and_zoom(self, x, y, zoom) -> Animation:
        return self.camera.frame.animate.move_to([x, y, 0]).scale(zoom)


class WorldBorder(VGroup):
    def __init__(self, plane: Plane,):
        super().__init__()
        thickness = 1
        opac = 0.9
        self.add(VGroup(
            Rectangle(width=thickness, height=12, color=WHITE,
                      fill_opacity=opac)
            .move_to(plane.c2p(-5 - thickness / 2, 0)),
            Rectangle(width=thickness, height=12, color=WHITE,
                      fill_opacity=opac)
            .move_to(plane.c2p(5 + thickness / 2, 0)),
            Rectangle(width=10, height=thickness, color=WHITE,
                      fill_opacity=opac)
            .move_to(plane.c2p(0, 5 + thickness / 2)),
            Rectangle(width=10, height=thickness, color=WHITE,
                      fill_opacity=opac)
            .move_to(plane.c2p(0, -5 - thickness / 2)),
        ))


class WorldGrid(VGroup):
    def __init__(self, plane: Plane):
        super().__init__()
        self.add(*[
            Line(plane.c2p(x, -5), plane.c2p(x, 5),
                 color=PURE_BLUE, stroke_width=1)
            for x in range(-5, 6)
        ])
        self.add(*[
            Line(plane.c2p(-5, y), plane.c2p(5, y),
                 color=PURE_BLUE, stroke_width=1)
            for y in range(-5, 6)
        ])


class RayLines:
    def __init__(self, vector: Vectors, player: Player):
        def unit_dir():
            v = vector.rotated_vec()
            n = np.linalg.norm(v[:2])
            return v if n == 0 else v / n

        self.unit_dir = unit_dir
        self.dot_pos = lambda d: player.get_center() + self.unit_dir() * d

        self.ray_len = ValueTracker(0)
        self.ray_line = always_redraw(lambda: Line(
            start=player.get_center(),
            end=player.get_center() + unit_dir() * self.ray_len.get_value(),
            color=PINK, stroke_width=4
        ))
        self.step = ValueTracker(0.5)

        def get_steps(step):
            random_steps = []
            max_len = self.ray_len.get_value()
            dist = 0
            while dist + step <= max_len:
                dist += step
                random_steps.append(dist)
            return random_steps

        self.get_steps = get_steps

        self.random_dots = always_redraw(lambda: VGroup(*[
            Dot(self.dot_pos(d), radius=0.04, color=RED if (
                self.dot_pos(d)[0] > 5
                or self.dot_pos(d)[1] > 5
            ) else PURE_GREEN)
            for d in self.get_steps(self.step.get_value()) if d <= self.ray_len.get_value()
        ]))


class Vectors:
    def __init__(self, player: Player):
        theta = ValueTracker(0)
        self.theta = theta

        def rotated_vec():
            x = player.ray_x.get_value()
            y = player.ray_y.get_value()
            t = theta.get_value()
            return np.array([
                x * np.cos(t) - y * np.sin(t),
                x * np.sin(t) + y * np.cos(t),
                0
            ])
        self.rotated_vec = rotated_vec

        self.ray_dir = always_redraw(lambda: Arrow(
            start=player.get_center(),
            end=player.get_center() + self.rotated_vec(),
            buff=0,
            color=PURE_RED,
            stroke_width=3,

        ))

        self.theta_label = always_redraw(lambda: MathTex(
            r"\theta=", font_size=24
        ))

        self.theta_value = always_redraw(lambda: DecimalNumber(
            self.theta.get_value(), num_decimal_places=2, color=YELLOW
        ).scale(0.5))

        self.rot_result = always_redraw(lambda: DecimalMatrix(
            [[self.rotated_vec()[0]],
             [self.rotated_vec()[1]]],
            element_to_mobject_config={
                "num_decimal_places": 2, "color": PURE_RED},
            bracket_config={"color": PURE_RED},
            left_bracket="[",
            right_bracket="]").scale(0.5).next_to(player, UP + LEFT, buff=0.3))

        self.explain_text = VGroup(
            VGroup(
                MarkupText("We can rotate that ", font_size=20),
                MathTex(
                    r"\vec{raydir}=\begin{bmatrix}x\\y\end{bmatrix}",
                    font_size=25
                ).set_submobject_colors_by_gradient(RED, PURE_BLUE),
            ).arrange(RIGHT, buff=0.2),

            MarkupText("by multiplying with a rotation matrix:",
                       font_size=20),
            MathTex(
                r"\vec{raydir}\,\begin{bmatrix}x\\y\end{bmatrix}'=\begin{bmatrix}\cos\theta&-\sin\theta\\\sin\theta&\cos\theta\end{bmatrix}\begin{bmatrix}x\\y\end{bmatrix}",
                font_size=25
            ).set_color_by_gradient(RED, PURE_BLUE),
        ).arrange(DOWN, aligned_edge=LEFT, buff=0.2).scale(0.8).next_to(self.ray_dir, UP * 1.5)
        self.group = SurroundingRectangle(
            self.explain_text, color=WHITE, buff=0.15, fill_color=BLACK,
            fill_opacity=1, corner_radius=0.2, stroke_width=3)


def intro(self: MovingCameraScene):
    with register_font("/home/toinou/Documents/vectors/fonts/Doom2016Left-RpJDA.ttf"):
        text1 = MarkupText(
            '<span letter_spacing="1000">CU</span>',
            font="Doom 2016 Left",
        ).scale(8).move_to(ORIGIN)
    with register_font("/home/toinou/Documents/vectors/fonts/Doom2016Text-GOlBq.ttf"):
        text2 = MarkupText(
            '<span letter_spacing="1000">B</span>',
            font="Doom2016Text",
        ).scale(8).move_to(ORIGIN)
    with register_font("/home/toinou/Documents/vectors/fonts/Doom2016Right-VGz0z.ttf"):
        text3 = MarkupText(
            '<span letter_spacing="1000">3D</span>',
            font="Doom 2016 Right",
        ).scale(8).move_to(ORIGIN)

    text = VGroup(text1, text2, text3).arrange(
        RIGHT, buff=0.2
    ).move_to(ORIGIN).set_color_by_gradient(
        ORANGE,
        BLUE,
    )
    self.wait()
    self.play(FadeIn(text))
    self.wait()
    self.play(FadeOut(text))
    lines = VGroup(
        VGroup(MarkupText("With a <b>given 2D</b> grid map, containing"),
               MarkupText(" <b>walls</b> (<b>1</b>) and <b>empty cells</b> (<b>0</b>).")).arrange(RIGHT, buff=0.2),
        MarkupText(
            "We reconstruct a <b>3D view</b> using the <b>raycasting</b> method."),
        VGroup(MarkupText(
            '<span foreground="red">Player</span>', weight=BOLD),
            MarkupText('has a starting position'),
            MathTex(r"\textbf{(x,y)}").set_color(GREEN).scale(1.5),
            MarkupText("and a view direction vector"),
            MathTex(r"\textbf{[x,y]}").set_color(RED).scale(1.5),

        ).arrange(RIGHT, buff=0.2),
        VGroup(MarkupText(
            '<span foreground="red">Player</span>', weight=BOLD),
            MarkupText('can move in <b>x</b> and <b>y axis continuously</b>')).arrange(RIGHT, buff=0.2)
    ).arrange(DOWN, aligned_edge=ORIGIN, buff=0.3).scale(0.65)
    lines.move_to(ORIGIN)
    self.add(lines)
    self.play(Write(lines), run_time=3)
    self.wait()
    self.play(Unwrite(lines, reverse=False), run_time=3)


def player_moving(self: MovingCameraScene, plane, walls, player: Player, pos_mat, panel, camera: FollowingCam):
    self.play(FadeIn(plane, walls))
    self.wait()
    player_anim = [
        FadeIn(player),
        Flash(player, num_lines=10, color=PURE_RED),
    ]
    self.play(AnimationGroup(*player_anim, lag_ratio=0.3),
              DrawBorderThenFill(panel))
    self.play(FadeIn(pos_mat))
    for _ in range(5):
        x = uniform(-4.8, 4.8)
        y = uniform(-4.8, 4.8)
        self.play(player.move(x, y), camera.move(x, y))
    x = 2.74
    y = 2.37
    self.play(player.move(x, y), camera.move(3.5, 3.5))
    self.play(AnimationGroup(
        (FadeOut(panel, pos_mat), camera.zoom(0.5)), lag_ratio=0.3))


def ray_length(self: MovingCameraScene, player: Player):
    line = MarkupText("How to find the exact lenght ?",
                      font_size=20).next_to(player, UP)

    lines = VGroup(
        VGroup(MarkupText("Let's say we have a ", font_size=20),
               MathTex(r"\vec{raydir}=\begin{bmatrix}x\\y\end{bmatrix}", font_size=25
                       ).set_submobject_colors_by_gradient(RED, PURE_BLUE),
               ).arrange(RIGHT, buff=0.2)
    ).arrange(DOWN, aligned_edge=ORIGIN, buff=0.3).next_to(player, UP)
    self.play(Write(line))
    self.play(Unwrite(line, reverse=False))
    self.play(Write(lines))
    self.play(Unwrite(lines, reverse=False))

    vectors = Vectors(player)
    vectors.explain_text.set_z_index(10)
    self.add(vectors.ray_dir)
    self.play(FadeIn(vectors.rot_result))
    self.play(player.ray_x.animate.set_value(1))
    self.play(vectors.theta.animate.set_value(0.6))
    self.play(FadeOut(vectors.rot_result), FadeOut(vectors.ray_dir))

    lines = RayLines(vectors, player)

    txt = MarkupText("We can put a random step")

    self.add(lines.ray_line, lines.random_dots)
    self.play(lines.ray_len.animate.set_value(6), run_time=3)
    self.play(lines.ray_len.animate.set_value(0), run_time=2)
    lines.step.set_value(0.1)
    self.play(lines.ray_len.animate.set_value(6), run_time=3)
    self.play(lines.ray_len.animate.set_value(0), run_time=2)
    self.wait(0.5)
    self.play(FadeOut(lines.random_dots))

    # def safe_inv(v):
    #     return 1.0 / max(abs(v), 1e-6)

    # delta_x = always_redraw(lambda: DecimalNumber(
    #     safe_inv(dir_vec()[0]), num_decimal_places=2, color=GREEN
    # ).scale(0.5))
    # delta_y = always_redraw(lambda: DecimalNumber(
    #     safe_inv(dir_vec()[1]), num_decimal_places=2, color=GREEN
    # ).scale(0.5))

    # delta_labels = VGroup(
    #     VGroup(MathTex(r"\Delta d_x=", font_size=24),
    #            delta_x).arrange(RIGHT, buff=0.1),
    #     VGroup(MathTex(r"\Delta d_y=", font_size=24),
    #            delta_y).arrange(RIGHT, buff=0.1),
    # ).arrange(DOWN, aligned_edge=LEFT, buff=0.15).next_to(player, UP + RIGHT, buff=0.3)

    # dda_len = ValueTracker(0)
    # dda_line = always_redraw(lambda: Line(
    #     start=player.get_center(),
    #     end=player.get_center() + unit_dir() * dda_len.get_value(),
    #     color=PURE_BLUE, stroke_width=4
    # ))

    # dda_dots = always_redraw(lambda: VGroup(*[
    #     Dot(player.get_center() + unit_dir() * d, radius=0.035, color=PURE_BLUE)
    #     for d in np.arange(
    #         0, min(dda_len.get_value(), 6),
    #         min(safe_inv(dir_vec()[0]), safe_inv(dir_vec()[1]))
    #     ) if d > 0
    # ]))

    # self.add(dda_line, dda_dots, delta_labels)
    # self.play(dda_len.animate.set_value(6), run_time=2)
    # self.wait(0.5)


class All(MovingCameraScene):
    def construct(self):
        plane = Plane()
        player = Player(0, 0)
        panel = Panel(player, self)
        camera = FollowingCam(self.camera)
        walls = WorldBorder(plane)

        pos_mat = always_redraw(lambda: DecimalMatrix(
            [[player.x.get_value(), player.y.get_value()]],
            element_to_mobject_config={
                "num_decimal_places": 2, "color": PURE_RED},
            bracket_config={"color": PURE_RED},
            left_bracket="(",
            right_bracket=")").scale(0.5).next_to(player, UP + RIGHT + IN * 2, buff=0.1))

        intro(self)
        player_moving(self, plane, walls, player, pos_mat, panel, camera)
        ray_length(self, player)

        # grid = WorldGrid(plane)

        # self.play(FadeIn(vectors.group), Write(vectors.explain_text))
        # self.wait(2)
        # self.play(AnimationGroup([Unwrite(
        #     vectors.explain_text, reverse=False), FadeOut(vectors.group)], lag_ratio=0.7))

        # self.wait()
