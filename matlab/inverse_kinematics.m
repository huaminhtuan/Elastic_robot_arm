function [q1, q2] = inverse_kinematics(x, y, z, curr_q1)
    l1 = 0.165;
    l2 = 0.2; 

    q2 = asin(((z-l1)/l2));

    if q2 == pi/2
        q1 = curr_q1;
    else
        if x == 0
            if curr_q1>0
                q1 = pi/2;
            else
                q1 = -pi/2;
            end
        else
            q1 = atan(y/x);
        end
    end
end