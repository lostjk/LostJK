gfx/effects/sabers/red_glow
{
	cull	twosided
    {
        map gfx/effects/sabers/red_glow2
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen vertex
    }
}

gfx/effects/sabers/red_line
{
	cull	twosided
    {
        map gfx/effects/sabers/red_line
        blendFunc GL_ONE GL_ONE
        rgbGen vertex
    }
}

gfx/effects/sabers/orange_glow
{
	cull	twosided
    {
        map gfx/effects/sabers/orange_glow2
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen vertex
    }
}

gfx/effects/sabers/orange_line
{
	cull	twosided
    {
        map gfx/effects/sabers/orange_line
        blendFunc GL_ONE GL_ONE
        rgbGen vertex
    }
}

gfx/effects/sabers/yellow_glow
{
	cull	twosided
    {
        map gfx/effects/sabers/yellow_glow2
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen vertex
    }
}

gfx/effects/sabers/yellow_line
{
	cull	twosided
    {
        map gfx/effects/sabers/yellow_line
        blendFunc GL_ONE GL_ONE
        rgbGen vertex
    }
}

gfx/effects/sabers/green_glow
{
	cull	twosided
    {
        map gfx/effects/sabers/green_glow2
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen vertex
    }
}

gfx/effects/sabers/green_line
{
	cull	twosided
    {
        map gfx/effects/sabers/green_line
        blendFunc GL_ONE GL_ONE
        rgbGen vertex
    }
}

gfx/effects/sabers/blue_glow
{
	cull	twosided
    {
        map gfx/effects/sabers/blue_glow2
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen vertex
    }
}

gfx/effects/sabers/blue_line
{
	cull	twosided
    {
        map gfx/effects/sabers/blue_line
        blendFunc GL_ONE GL_ONE
        rgbGen vertex
    }
}

gfx/effects/sabers/purple_glow
{
	cull	twosided
    {
        map gfx/effects/sabers/purple_glow2
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen vertex
    }
}

gfx/effects/sabers/purple_line
{
	cull	twosided
    {
        map gfx/effects/sabers/purple_line
        blendFunc GL_ONE GL_ONE
        rgbGen vertex
    }
}

gfx/effects/sabers/saberBlur
{
	cull	twosided
    {
        clampmap gfx/effects/sabers/blurglow
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen vertex
    }
    {
        clampmap gfx/effects/sabers/blurcore
        blendFunc GL_ONE GL_ONE
        rgbGen identity
    }
}

gfx/effects/sabers/swordTrail
{
	qer_editorimage	gfx/effects/sabers/blurglow
	nopicmip
	nomipmaps
	cull	twosided
    {
        clampmap gfx/effects/sabers/swordtrail
        blendFunc GL_ONE GL_ONE
        glow
        rgbGen vertex
    }
}

