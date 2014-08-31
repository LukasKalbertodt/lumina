![alt](https://raw.githubusercontent.com/LukasKalbertodt/lumina/master/_media/GitHubHeader.png)

Lumina is a C++ OpenGL graphics library with the following design principles:
* *lightweight*: Just provide features which are necessary 
* *modern*: Use C++11 features where it's appropriat (Maybe using C++14 features in future versions)
* *render-pipeline-abstraction*: Make it easy to use the OpenGL pipeline but don't provide high level functions like game engines would
* *little-overhead*: Don't do too much that the user may not want to do


This is the first working release of lumina and there is a lot more work to do. Everything can change in newer versions. The first major version (1.0) will have a fixed API that won't change anymore. 

## How does it look like?
One important class is the `VertexSeq` which represents a list of vertices with a given order. It's implemented with one vertex buffer and one index buffer internally. The design goal of this class was to provide type-safe functionality that isn't too complex and does exactly how the user thinks about a sequence of vertices. 
To create a quad (4 vertices) where each vertex has a position and a UV-coordinate you could write:

    // each vertex contains a vector of 3 floats (pos) and a vector of 2 floats (uv)
    VertexSeq<Vec3f, Vec2f> seq;
    
    // we need 4 vertices
    seq.create(4);
    
    seq.prime([](auto& hotSeq) {
      hotSeq.vertex[0].set(Vec3f(1.f, 0.f, 1.f), Vec2f(0.f, 0.f));
      hotSeq.vertex[0].set(Vec3f(0.f, 0.f, 1.f), Vec2f(1.f, 0.f));
      hotSeq.vertex[0].set(Vec3f(0.f, 1.f, 1.f), Vec2f(0.f, 1.f));
      hotSeq.vertex[0].set(Vec3f(1.f, 1.f, 1.f), Vec2f(1.f, 1.f));
    });
    
The VertexSeq uses the type information to do all kinds of checks (type checks, bound checks, etc) and to gather different information to create a vertex buffer of correct size or tell OpenGL the necessary vertex layout information.

*Note*: The primitive type is not part of the sequence, but is specified when drawing a sequence only.
