PGDMP         
            	    x            postgres    13.0    13.0 !    �           0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                      false            �           0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                      false            �           0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                      false            �           1262    13442    postgres    DATABASE     e   CREATE DATABASE postgres WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE = 'Russian_Russia.1251';
    DROP DATABASE postgres;
                postgres    false            �           0    0    DATABASE postgres    COMMENT     N   COMMENT ON DATABASE postgres IS 'default administrative connection database';
                   postgres    false    3022                        3079    16384 	   adminpack 	   EXTENSION     A   CREATE EXTENSION IF NOT EXISTS adminpack WITH SCHEMA pg_catalog;
    DROP EXTENSION adminpack;
                   false            �           0    0    EXTENSION adminpack    COMMENT     M   COMMENT ON EXTENSION adminpack IS 'administrative functions for PostgreSQL';
                        false    2            �            1259    16433    cards    TABLE     �   CREATE TABLE public.cards (
    cvv text NOT NULL,
    month text NOT NULL,
    name text NOT NULL,
    number text NOT NULL,
    year text NOT NULL,
    surname text NOT NULL,
    id_card integer NOT NULL,
    login text NOT NULL
);
    DROP TABLE public.cards;
       public         heap    postgres    false            �            1259    16457    cards_id_card_seq    SEQUENCE     �   CREATE SEQUENCE public.cards_id_card_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 (   DROP SEQUENCE public.cards_id_card_seq;
       public          postgres    false    202            �           0    0    cards_id_card_seq    SEQUENCE OWNED BY     G   ALTER SEQUENCE public.cards_id_card_seq OWNED BY public.cards.id_card;
          public          postgres    false    203            �            1259    16509 
   operations    TABLE     |   CREATE TABLE public.operations (
    operation_id integer NOT NULL,
    user_id integer NOT NULL,
    json text NOT NULL
);
    DROP TABLE public.operations;
       public         heap    postgres    false            �            1259    16507    operations_operation_id_seq    SEQUENCE     �   CREATE SEQUENCE public.operations_operation_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 2   DROP SEQUENCE public.operations_operation_id_seq;
       public          postgres    false    206            �           0    0    operations_operation_id_seq    SEQUENCE OWNED BY     [   ALTER SEQUENCE public.operations_operation_id_seq OWNED BY public.operations.operation_id;
          public          postgres    false    205            �            1259    16421    people    TABLE     �   CREATE TABLE public.people (
    login text NOT NULL,
    password text NOT NULL,
    surname text NOT NULL,
    name text NOT NULL,
    patronymic text NOT NULL,
    phone text NOT NULL,
    user_id integer NOT NULL,
    score text NOT NULL
);
    DROP TABLE public.people;
       public         heap    postgres    false            �            1259    16488    people_user_id_seq    SEQUENCE     �   CREATE SEQUENCE public.people_user_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 )   DROP SEQUENCE public.people_user_id_seq;
       public          postgres    false    201            �           0    0    people_user_id_seq    SEQUENCE OWNED BY     I   ALTER SEQUENCE public.people_user_id_seq OWNED BY public.people.user_id;
          public          postgres    false    204            3           2604    16459    cards id_card    DEFAULT     n   ALTER TABLE ONLY public.cards ALTER COLUMN id_card SET DEFAULT nextval('public.cards_id_card_seq'::regclass);
 <   ALTER TABLE public.cards ALTER COLUMN id_card DROP DEFAULT;
       public          postgres    false    203    202            4           2604    16512    operations operation_id    DEFAULT     �   ALTER TABLE ONLY public.operations ALTER COLUMN operation_id SET DEFAULT nextval('public.operations_operation_id_seq'::regclass);
 F   ALTER TABLE public.operations ALTER COLUMN operation_id DROP DEFAULT;
       public          postgres    false    206    205    206            2           2604    16490    people user_id    DEFAULT     p   ALTER TABLE ONLY public.people ALTER COLUMN user_id SET DEFAULT nextval('public.people_user_id_seq'::regclass);
 =   ALTER TABLE public.people ALTER COLUMN user_id DROP DEFAULT;
       public          postgres    false    204    201            �          0    16433    cards 
   TABLE DATA           X   COPY public.cards (cvv, month, name, number, year, surname, id_card, login) FROM stdin;
    public          postgres    false    202   `#       �          0    16509 
   operations 
   TABLE DATA           A   COPY public.operations (operation_id, user_id, json) FROM stdin;
    public          postgres    false    206   �#       �          0    16421    people 
   TABLE DATA           c   COPY public.people (login, password, surname, name, patronymic, phone, user_id, score) FROM stdin;
    public          postgres    false    201   �$       �           0    0    cards_id_card_seq    SEQUENCE SET     @   SELECT pg_catalog.setval('public.cards_id_card_seq', 20, true);
          public          postgres    false    203            �           0    0    operations_operation_id_seq    SEQUENCE SET     J   SELECT pg_catalog.setval('public.operations_operation_id_seq', 23, true);
          public          postgres    false    205            �           0    0    people_user_id_seq    SEQUENCE SET     @   SELECT pg_catalog.setval('public.people_user_id_seq', 5, true);
          public          postgres    false    204            :           2606    16468    cards cards_pkey 
   CONSTRAINT     S   ALTER TABLE ONLY public.cards
    ADD CONSTRAINT cards_pkey PRIMARY KEY (id_card);
 :   ALTER TABLE ONLY public.cards DROP CONSTRAINT cards_pkey;
       public            postgres    false    202            >           2606    16517    operations operations_pkey 
   CONSTRAINT     b   ALTER TABLE ONLY public.operations
    ADD CONSTRAINT operations_pkey PRIMARY KEY (operation_id);
 D   ALTER TABLE ONLY public.operations DROP CONSTRAINT operations_pkey;
       public            postgres    false    206            6           2606    16428    people people_pkey 
   CONSTRAINT     S   ALTER TABLE ONLY public.people
    ADD CONSTRAINT people_pkey PRIMARY KEY (login);
 <   ALTER TABLE ONLY public.people DROP CONSTRAINT people_pkey;
       public            postgres    false    201            8           2606    16519    people user_id_unq 
   CONSTRAINT     P   ALTER TABLE ONLY public.people
    ADD CONSTRAINT user_id_unq UNIQUE (user_id);
 <   ALTER TABLE ONLY public.people DROP CONSTRAINT user_id_unq;
       public            postgres    false    201            ;           1259    16478    fki_login_fkey    INDEX     A   CREATE INDEX fki_login_fkey ON public.cards USING btree (login);
 "   DROP INDEX public.fki_login_fkey;
       public            postgres    false    202            <           1259    16525    fki_user_id_fkey    INDEX     J   CREATE INDEX fki_user_id_fkey ON public.operations USING btree (user_id);
 $   DROP INDEX public.fki_user_id_fkey;
       public            postgres    false    206            ?           2606    16473    cards login_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.cards
    ADD CONSTRAINT login_fkey FOREIGN KEY (login) REFERENCES public.people(login) ON UPDATE CASCADE ON DELETE CASCADE NOT VALID;
 :   ALTER TABLE ONLY public.cards DROP CONSTRAINT login_fkey;
       public          postgres    false    202    2870    201            @           2606    16520    operations user_id_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.operations
    ADD CONSTRAINT user_id_fkey FOREIGN KEY (user_id) REFERENCES public.people(user_id) NOT VALID;
 A   ALTER TABLE ONLY public.operations DROP CONSTRAINT user_id_fkey;
       public          postgres    false    201    2872    206            �   �   x�]�A�0��Ǡ&v����%	��Jը�ǉ��z�f,{�R���S�N<**	N�m݉�G@N%c�H�Xm�.� /�_}'�ꟶ8U_s���A����5>��&RU(����7��!�!�/�z��>�1�      �   �   x����
�0 ����g�6i��oD�;(2�$��'���a���7����xMR�3�]�v�V��y��[#&���H����T�S}jvu���[ѽ���^paA�Ź,�Xxh�m_�cv>������\sG	�  
���-VY���)rbyH��CM����(,��'�1OS�"6�bNS.#E��LQ$��=���Q�A������#��&�J�jc�Aa�y����D;      �   �   x�M�K�0D�� U�����D%|�
%D��}�3�����C�wTB�,t��+j���$JZ��?On�X�A��<��)�mm�Ц�Yx���K:6zb�2J��A��Lo?#�O�NԒ���UFI�P)�`+�y#�Z7�     