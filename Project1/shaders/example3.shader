#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
uniform float offset;

out vec4 ourColor;

void main() {
  gl_Position = vec4(aPos.x + offset, -aPos.y, aPos.z, 1.0);
  ourColor = gl_Position;
}


#shader fragment
#version 330 core
in vec4 ourColor;
out vec4 FragColor;

void main() {
  FragColor = ourColor; // vec4(1.0f, 0.5f, 0.2f, 1.0f);
}