subroutine vec4 LinghtFunc(vec3);

subroutine (LinghtFunc) vec4 ambient(vec3 n)
{
    return Materials.ambient;
}
subroutine (LinghtFunc) vec4 diffuse(vec3 n)
{
    return Materials.diffuse * max(dot(nomalize(n), LinghtFunc.xyz), 0.0);
}

subroutine uniform LinghtFunc materialsShader;