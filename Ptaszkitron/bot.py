import os
import discord
import youtube_dl
import random
from discord.ext import commands
from discord import FFmpegPCMAudio

TOKEN = 'token here'


intents = discord.Intents.default()
intents.members = True
intents.message_content = True

#client = discord.Client(activity=discord.Activity(name='Lives in computer'), intents=intents)
client = commands.Bot(command_prefix='/', intents=intents)
#FFMPEG_OPTIONS = {'before_options': '-reconnect 1 -reconnect_streamed 1 -reconnect_delay_max 5', 'options': '-vn'}

@client.event 
async def on_ready():
    print(f'Bot is ready. ({client.user})')


@client.event
async def on_member_join(member):
    print(f'{member} has joined a server.')


@client.event
async def on_member_remove(member):
    print(f'{member} has left a server.')


@client.listen('on_message')
async def on_message(message):
    print(f'>>Message: {message.author} Ad: {message.channel} ULink=({message.author.id}) ChLink=({message.channel.id}), MLink=({message.id}) ::\n{message.content}')
    if message.author == client.user: return

    if message.content.startswith('hi bot'):
        await message.channel.send('hi human')
    if message.content.startswith('dm me bot'):
        await message.author.send('hello there :D')
    

@client.command(name='ping', help='Displayes latency.')
async def ping(ctx):
    await ctx.send(f'Ping: {round(client.latency * 1000)}ms')


@client.command(name='send', help='Sends image from database.')
async def send(ctx, animal):
    if animal == 'cat':
        await ctx.message.add_reaction('🐈')
        await ctx.send(f'here\'s cat', file=discord.File('send_cat.jpg'))
    if animal == 'dog':
        await ctx.message.add_reaction('🐕')
        await ctx.send(f'here\'s dog', file=discord.File('send_dog.jpg'))


@client.command(name='find', help='Finds messages with a given words.')
async def find(ctx, word, author=None):
    from_channel = client.get_channel(ctx.message.channel.id)
    first = True
    async for msg in from_channel.history(limit=200):
        if first == True:
            first = False
            continue
        if author is not None and msg.author.mention != author:
                continue
        if word in msg.content and first == False and not (msg.author == client.user and 'Url for the message' in msg.content):
            await ctx.send(f'**Url for the message:** {msg.jump_url}\n**Message:** {msg.author} - "{msg.content}"')


@client.command(name='getmsg', help='Downloads messages of a given user.')
async def get_msg(ctx, author, channel=None):
    if channel == None:
        from_base = ctx.guild.text_channels
        with open(author.strip('<@>')+'.txt', 'w', encoding='utf-8') as file:
            for channel in from_base:
                async for msg in channel.history():
                    if msg.author.mention == author and msg.content is not '':
                        file.write(msg.content+'\n<:>SPACE<:>\n')
    else:
        from_base = client.get_channel(int(channel.strip('<#>')))
        with open(author.strip('<@>')+'.txt', 'w', encoding='utf-8') as file:
            async for msg in from_base.history():
                if msg.author.mention == author:
                    file.write(msg.content+'\n<:>SPACE<:>\n')
    await ctx.send('Done!')


@client.command(name='startsim', help='Mimics given user if they exist in database.')
async def simulate(ctx, author=None):
    if author == None:
        author = 'mimic'
    if os.path.exists(author.strip('<@>')+'.txt'):
        with open(author.strip('<@>')+'.txt', 'r', encoding='utf-8') as file:
            author_database = []
            message = ''
            for line in file:
                if line == '<:>SPACE<:>\n':
                    author_database.append(message)
                    message = ''
                    continue
                message += line
        await ctx.send(f'Simulation ready!\nI have {len(author_database)} messages to choose from :D')
        while True:
            user_message = await ctx.bot.wait_for('message', timeout=180)
            if user_message.content == '/stopsim':
                await ctx.send('Simulation stopped!')
                break
            else:
                response_msg = find_response(user_message.content, author_database)
                if response_msg is not None:
                    await ctx.send(response_msg)
    else:
        await ctx.send('I have no database for this user :(')


@client.command(name='join', help='Joins the user voice channel.')
async def join(ctx):
    await ctx.author.voice.channel.connect()


@client.command(name='leave', help='Leaves the voice channel.')
async def leave(ctx):
    await ctx.voice_client.disconnect()


@client.command(name='play', help='Playes given music/sound.')
async def play(ctx, url):
    if ctx.voice_client:
        if url == 'frog':
            ctx.voice_client.stop()
            ctx.voice_client.play(FFmpegPCMAudio(executable='C:/FFmpeg/bin/ffmpeg.exe', source='play_frog.mp3'))
        else:
            ctx.voice_client.stop()
            ctx.voice_client.play(FFmpegPCMAudio(executable='C:/FFmpeg/bin/ffmpeg.exe', source=url))


def find_response(user_message, author_database):
    response_msg = None
    max = 0
    question = False
    if '?' in user_message:
        question = True
    user_message = user_message.lower().strip(',.:/?').split(' ')
    for msg in author_database:
        if question and '?' in msg:
            continue
        check_msg = msg.lower().strip(',.:/?').split(' ')
        common_words = set(user_message).intersection(check_msg)
        current = len(common_words)
        if current > max or (current == max and random.randint(0,1) == 0):
            response_msg = msg
            max = current
    return response_msg

client.run(TOKEN)