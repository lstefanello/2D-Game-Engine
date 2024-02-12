IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -O3

ODIR=obj

LIBS=-lSDL2 -lglut -lGLEW `sdl2-config --libs` -lGL -ldl

#_DEPS=imgui.h imgui_impl_opengl3.h imgui_impl_sdl.h imgui_internal.h imstb_rectpack.h imstb_textedit.h imstb_truetype.h ECS.h StateManager.h Game.h Components.h DisplayManager.h stb_image.h Utilities.h Text.h Globals.h RenderSystem.h KeyboardControlledSystem.h ApplyVelocitySystem.h ColorRotationPosSystem.h CollisionSystem.h ParticleSystem.h DestructSystem.h AnimationSystem.h DepthSystem.h ShootSystem.h FollowMouseSystem.h Main_State.h AttractorSystem.h

_DEPS=ECS.h StateManager.h Game.h Components.h DisplayManager.h stb_image.h Utilities.h Text.h Globals.h RenderSystem.h KeyboardControlledSystem.h ApplyVelocitySystem.h ColorRotationPosSystem.h CollisionSystem.h ParticleSystem.h DestructSystem.h AnimationSystem.h DepthSystem.h ShootSystem.h FollowMouseSystem.h Main_State.h AttractorSystem.h OffScreenDestroySystem.h LightSourceSystem.h CameraSystem.h FrustumCullingSystem.h FloatSystem.h FollowSystem.h

DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

#_OBJ=main.o imgui.o imgui_impl_opengl3.o imgui_impl_sdl.o imgui_draw.o imgui_tables.o imgui_widgets.o ECS.o StateManager.o Game.o Systems.o DisplayManager.o Utilities.o Game.o Text.o CollisionSystem.o KeyboardControlledSystem.o RenderSystem.o ApplyVelocitySystem.o ColorRotationPosSystem.o AnimationSystem.o Globals.o ParticleSystem.o DestructSystem.o DepthSystem.o ShootSystem.o FollowMouseSystem.o Main_State.o AttractorSystem.o

_OBJ=main.o ECS.o StateManager.o Game.o Systems.o DisplayManager.o Utilities.o Game.o Text.o CollisionSystem.o KeyboardControlledSystem.o RenderSystem.o ApplyVelocitySystem.o ColorRotationPosSystem.o AnimationSystem.o Globals.o ParticleSystem.o DestructSystem.o DepthSystem.o ShootSystem.o FollowMouseSystem.o Main_State.o AttractorSystem.o OffScreenDestroySystem.o LightSourceSystem.o CameraSystem.o FrustumCullingSystem.o FloatSystem.o FollowSystem.o

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

engine: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
