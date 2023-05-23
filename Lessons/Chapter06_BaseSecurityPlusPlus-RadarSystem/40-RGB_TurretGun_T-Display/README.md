## Story Synopsis:

T-Display version

NOTE: PWM works differently than on the HERO XL.  We have to separately set up the
      PWM channels and frequencies and attach those channels to the appropriate pins.
      Lastly, use the ledcWrite() function instead of analogWrite().

Our homebuilt sonar is showing that, yes, there are AI "scouts" checking us out.

It appears that they are receiving their commands via light based communications,
so we can't use a radio jammer to disrupt them, but it appears that if we shine
a focused beam of variable colored light at the intruders they seem to lock up.

Let's set up a turret that we can remote control with our new "light gun" and see
if we can deal with these intruders!

