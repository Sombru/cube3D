/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:47:14 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/11 13:55:04 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

// +map will be first parsed into array of strings
// +the amount of strings is map_y
// +the longest string is map_x
// +spaces will be converted into walls
// +tabs into 4 walls
// +player_a will depend on weather is N, W, E ,S is player
// chek validity of the map and memory leaks

static unsigned int	rgb_to_hex(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

static char **get_config(int fd, t_data *data)
{
    char **config;
    int i;

    config = malloc(sizeof(config) * (7));
    i = 0;
    while (i <= 6)
    {
        config[i] = get_next_line(fd);
        if (!config[i])
            exit(write(2, "not valid map format\n", 22));
        config[i] = ft_rmlast_char(config[i], '\n');
        i++;
    }
    i = 0;
    while (i <= 3)
    {
        config[i] = ft_strchr(config[i], '/');
        if(!config[i])
            exit(write(2, "not valid textures\n", 20));
        config[i]++;
        data->textures[i] = config[i];
        i++;
    }
    return(config);
}

static char	*get_map_line(char *map, t_data *data)
{
    char	*res;
    int		i;
    int		j;

    res = malloc(sizeof(char) * (data->map_x + 1));
    if (!res)
        return (NULL);
    i = 0;
    j = 0;
    while (map[i])
    {
        if (map[i] == ' ')
        {
            res[j++] = '1';
        }
        else if (map[i] == '\t')
        {
            res[j++] = '1';
            res[j++] = '1';
            res[j++] = '1';
            res[j++] = '1';
        }
        else
        {
            res[j++] = map[i];
        }
        i++;
    }
    while (j < data->map_x)
    {
        res[j++] = '1';
    }
    res[j] = '\0';

    return (res);
}

static char	**parse_map(int fd, t_data *data)
{
    char *map[200];
    char **parsed;
    int	x;
    int	y;
    
    map[0] = get_next_line(fd);
    while (map[0][0] == '\n')
    {
        free(map[0]);
        map[0] = get_next_line(fd);
    }
    map[0] = ft_rmlast_char(map[0], '\n');
    x = 0;
    y = 1;
    while (1)
    {
        map[y] = get_next_line(fd);
        if (!map[y])
            break ;
        map[y] = ft_rmlast_char(map[y], '\n');
        if ((int)ft_strlen(map[y]) > x)
            x = ft_strlen(map[y]);
        y++;
    }
    data->map_y = y;
    data->map_x = x;
    parsed = malloc(sizeof(char *) * (data->map_y + 1));
    if (!parsed)
        return (NULL);
    y = 0;
    while (y < data->map_y)
    {
        parsed[y] = get_map_line(map[y], data);
        y++;
    }
    parsed[y] = NULL;
    
    printf("data->map_y: %d\n", data->map_y);
    printf("data->map_x: %d\n", data->map_x);
    debug_map(parsed);
    return(parsed);
}

char	*get_map(char *map_path, t_data *data)
{
    int		fd;
    char	**map_parse;
    char	**config;
    char	**rgb_values;
    int		rgb[6];
    int		i;

    fd = open(map_path, O_RDONLY);
    if (fd == -1)
        exit(write(2, "could not open the file\n", 25));
    config = get_config(fd, data);
    if (config[5][0] == 'F' || config[6][0] == 'C')
    {
        i = 0;
        rgb_values = ft_split(config[5] + 2, ',');
        while (i <= 2)
        {
            rgb[i] = ft_atoi(rgb_values[i]);
            i++;
        }
        ft_free_array(rgb_values);
        if (config[5][0] == 'F')
            data->floor_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
        rgb_values = ft_split(config[6] + 2, ',');
        while (i <= 5)
        {
            rgb[i] = ft_atoi(rgb_values[i - 3]);
            i++;
        }
        ft_free_array(rgb_values);
        if (config[6][0] == 'C')
            data->ceiling_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
    }
    printf("data->textures: %s\n", data->textures[0]);
    printf("data->textures: %s\n", data->textures[1]);
    printf("data->textures: %s\n", data->textures[2]);
    printf("data->textures: %s\n", data->textures[3]);
    printf("floor: %X\n", data->floor_color);
    printf("ceiling: %X\n", data->ceiling_color);
    map_parse = parse_map(fd, data);
    close(fd);

    data->map = malloc(data->map_x * data->map_y + 1);
    if (!data->map)
        exit(write(2, "Memory allocation failed\n", 26));
    i = 0;
    int j = 0;
    while (map_parse[i])
    {
        int k = 0;
        while (map_parse[i][k])
        {
            if (map_parse[i][k] == 'N' || map_parse[i][k] == 'S' || map_parse[i][k] == 'E' || map_parse[i][k] == 'W')
            {
                data->player_x = k * data->block_size + data->block_size / 2;
                data->player_y = i * data->block_size + data->block_size / 2;
                if (map_parse[i][k] == 'N')
                    data->player_a = 3 * PI / 2;
                else if (map_parse[i][k] == 'S')
                    data->player_a = PI / 2;
                else if (map_parse[i][k] == 'E')
                    data->player_a = 0;
                else if (map_parse[i][k] == 'W')
                    data->player_a = PI;
                data->player_d_x = cos(data->player_a);
                data->player_d_y = sin(data->player_a);
                data->map[j++] = '0'; // Replace player start pos
            }
            else
            {
                data->map[j++] = map_parse[i][k];
            }
            k++;
        }
        i++;
    }
    data->map[j] = '\0';

    ft_free_array(map_parse);
    return ("tst");
}
